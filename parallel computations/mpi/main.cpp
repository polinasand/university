#include <iostream>
#include <mpi.h>
#include <string>
#include <conio.h>
#include <time.h>
#include <cmath>

using namespace std;

struct point{
    double x;
    double y;
    point() {
        x = 0;
        y = 0;
    }
    point(double _x, double _y){
        x = _x;
        y = _y;
    }
};
int procNum; // Number of available processes
int procRank; // Rank of current process

void init(point* &points, pair<point, point>* &procPoints, int& N, int& NP, int& procNP);
void dataDist(point* points, pair<point, point>* &procPoints, int N, int NP, int procNP);
void testDist(point* points, pair<point, point>* procPoints, int N, int procNP);
double serialSearch(point* points, point* &serialRes, int N);
void parallelSearch(point* points, pair<point, point>* procPoints, point* &procRes, int N,  int procNP);
void getRes(point* procRes, point* &res, int N, int NP, int procNP);
void testRes(point* points, point* res, int N);
void termination(point* &points, pair<point, point>* &procPoints, point* &res, point* &procRes);

double triangleSqr(point A, point B, point C);
void printPairs(pair<point, point>* procPoints, int procNP);
void printRes(point* res);
void printPoint(point p);
void getFromFile(int& N, int& NP, point* &points);
void randomInit(int& N, int& NP, point* &points);

int main(int argc, char* argv[])
{
    point* points; // list of N points
    pair<point, point>* procPoints; // list of pairs of curr procNP points
    int N; // number of points
    int NP; // total number of pairs of points
    int procNP; // curr number of pairs of points
    point* res; // common res vector of size RP
    point *procRes;
    procRes = new point[3]; // vector of 3 result points

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &procNum);
    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
    int RP = 3*procNum;
    res = new point[RP];

    init(points, procPoints, N, NP, procNP);

    //double start = MPI_Wtime();
    dataDist(points, procPoints, N, NP, procNP);
    testDist(points, procPoints, N, procNP);
    parallelSearch(points, procPoints, procRes, N, procNP);
    getRes(procRes, res, N, NP, procNP);

    /*double finish = MPI_Wtime();



    if (procRank == 0) {
        cout << "Time of execution = "<<finish-start << endl;
    }*/
    testRes(points, res, N);
    termination(points, procPoints, res, procRes);

    MPI_Finalize();
    return 0;
}

void init(point* &points, pair<point, point>* &procPoints, int& N, int& NP,int& procNP) {
    if (procRank == 0) {
        //getFromFile(N, NP, points);
        randomInit(N, NP, points);
        for (int i=0; i<N;i ++)
            printPoint(points[i]);
    }

    MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&NP, 1, MPI_INT, 0, MPI_COMM_WORLD);
    //cout << N << ' '<<NP<<endl;

    MPI_Datatype mpi_point;
    MPI_Type_contiguous(2, MPI_DOUBLE, &mpi_point);
    MPI_Type_commit(&mpi_point);

    // Determine the number of pair of points stored on each process
    int restNP = NP;
    for (int i=0; i<procRank; i++)
        restNP = restNP - restNP/(procNum-i);
    procNP = restNP/(procNum - procRank);

    procPoints = new pair<point, point>[procNP];
}

void dataDist(point* points, pair<point, point>* &procPoints, int N, int NP, int procNP) {

    int *pSendNum;
    pSendNum = new int [procNum];// the number of elements sent to the process
    int *pSendInd;
    pSendInd = new int [procNum]; // the index of the first data element sent to the process
    int restNP = NP; // Number of rows, that haven’t been distributed yet

    MPI_Datatype mpi_point;
    MPI_Type_contiguous(2, MPI_DOUBLE, &mpi_point);
    MPI_Type_commit(&mpi_point);

    MPI_Bcast(points, N, mpi_point, 0, MPI_COMM_WORLD);

    procNP = restNP / procNum;
    pSendNum[0] = procNP;
    pSendInd[0] = 0;
    //cout << pSendNum[0] << ' ' << pSendInd[0] << endl;
    for (int i=1; i<procNum; i++) {
        restNP -= procNP;
        procNP = restNP/(procNum - i);
        pSendNum[i] = procNP;
        pSendInd[i] = pSendInd[i-1] + pSendNum[i-1];
        cout <<"sends "<< pSendNum[i] << ' ' << pSendInd[i] << endl;
    }

    pair<point, point>* pairs;
    pairs = new pair<point, point> [NP];
    int k = 0;
    for (int i=0; i < N-1; i++){
        for (int j=i+1; j < N; j++) {
            if (k >= NP)
                break;
            pair <point, point> p = make_pair(points[i], points[j]);
            pairs[k] = p;
            k++;
        }
    }

    MPI_Datatype mpi_point_pair;
    MPI_Type_contiguous(2, mpi_point, &mpi_point_pair);
    MPI_Type_commit(&mpi_point_pair);

    MPI_Scatterv(pairs, pSendNum, pSendInd, mpi_point_pair, procPoints, pSendNum[procRank], mpi_point_pair, 0, MPI_COMM_WORLD);

    delete [] pSendNum;
    delete [] pSendInd;
}

void testDist(point* points, pair<point, point>* procPoints, int N, int procNP) {
    MPI_Barrier(MPI_COMM_WORLD);
    for (int i=0; i<procNum; i++) {
        if (procRank == i) {
            printf("\nProcRank = %d \n", procRank);
            printPairs(procPoints, procNP);
        }
        MPI_Barrier(MPI_COMM_WORLD);
    }
}

double serialSearch(point* points, point* &serialRes, int N) {
    double ans = 0, currS;
    serialRes = new point[3];
    for (int i = 0; i < N; i++){
        for (int j=i+1; j < N; j++){
            for (int k=j+1; k<N; k++){
                if (i != j && j != k && i != k) {
                    currS = triangleSqr(points[i], points[j], points[k]);
                    if (currS > ans) {
                        ans = currS;
                        serialRes[0] = points[i];
                        serialRes[1] = points[j];
                        serialRes[2] = points[k];
                    }
                }
            }
        }
    }
    return ans;
}


double triangleSqr(point A, point B, point C) {
    double a = sqrt((C.x-B.x)*(C.x-B.x) + (C.y-B.y)*(C.y-B.y));
    double b = sqrt((A.x-C.x)*(A.x-C.x) + (A.y-C.y)*(A.y-C.y));
    double c = sqrt((A.x-B.x)*(A.x-B.x) + (A.y-B.y)*(A.y-B.y));
    double p = (a + b + c)/2;
    return sqrt(p*(p-a)*(p-b)*(p-c));
}

void printPairs(pair<point, point>* procPoints, int procNP) {
    for (int i=0; i<procNP; i++){
        printf("(%f; %f) (%f; %f)\n", procPoints[i].first.x, procPoints[i].first.y,
               procPoints[i].second.x, procPoints[i].second.y);
    }
}

void printPoint(point p) {
    printf("(%f; %f)\n", p.x, p.y);
}

void printRes(point* res) {
    for (int i=0; i< 3; i++)
        printf("(%f; %f)\n", res[i].x, res[i].y);
}

void getFromFile(int& N, int& NP, point* &points) {
    freopen("in.txt", "r", stdin);
        cin >> N;
        points = new point [N];
        NP = N*(N-1)/2;
        double x, y;
        for (int i=0; i<N; i++){
            if (cin >> x >> y){
                points[i] = point(x, y);
                printPoint(points[i]);
            }

        }
}

void randomInit(int& N, int& NP, point* &points) {
    //srand(time(nullptr));

    N = rand() % 6+1;
    NP = N*(N-1)/2;
    points = new point[N];
    for (int i=0; i<N; i++){
        points[i] = point(rand() % 10, rand()%10);
    }
}


void parallelSearch(point* points, pair<point, point>* procPoints, point* &procRes, int N, int procNP) {
    double ans = 0, currS;
    for (int i=0; i<N; i++){
        for (int j=0; j<procNP; j++){
            point A = points[i];
            point B = procPoints[j].first;
            point C = procPoints[j].second;
            currS = triangleSqr(A, B, C);
            if (currS > ans && currS > 0){
                ans = currS;
                procRes[0] = A;
                procRes[1] = B;
                procRes[2] = C;
            }
        }
    }
    cout << procRank<<" points are " << procRes[0].x << endl;
}
void getRes(point* procRes, point* &res, int N, int NP, int procNP) {
    MPI_Datatype mpi_point;
    MPI_Type_contiguous(2, MPI_DOUBLE, &mpi_point);
    MPI_Type_commit(&mpi_point);
    int RP = 3*procNum;
    MPI_Allgather(procRes, 3, mpi_point, res, RP, mpi_point, MPI_COMM_WORLD);

}

void testRes(point* points, point* res, int N) {
    if (procRank == 0){
        cout << "\nSerial result: \n";
        point* serialRes;
        double ans = serialSearch(points, serialRes, N);
        for (int i=0; i<3; i++){
            printPoint(serialRes[i]);
        }
        cout << "square is "<< ans <<endl;

        ans = 0;
        double currS=0;
        int t = 0;
        for (int i=0; i<3*procNum; i+=3){
            currS = triangleSqr(res[i], res[i+1], res[i+2]);
            if (currS > ans){
                t = i - i%3;
                ans = currS;
            }
        }
        cout << "\nParallel result: \n";
        printPoint(res[t]);
        printPoint(res[t+1]);
        printPoint(res[t+2]);
        cout << "square is "<< ans<<endl;
    }
}

void termination(point* &points, pair<point, point>* &procPoints, point* &res,point* &procRes) {
    if (procRank == 0){
        delete [] points;

    }
    delete [] res;
        delete [] procPoints;
        delete [] procRes;
}
