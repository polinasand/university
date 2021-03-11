#include <iostream>
#include <mpi.h>
#include <string>
#include <conio.h>
#include <time.h>
#include <cmath>
#include<vector>
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

void init(vector<point> &points, int& N, vector<point> &res, vector<pair<point, point>> &procPoints, vector<point> &procRes, int& procNP);
void dataDist(vector<point> &points, vector<pair<point, point>> &procPoints, int N, int procNP);
void testDist(vector<point> &points, vector<pair<point, point>> &procPoints, int N, int procNP);
void serialSearch(vector<point> &points, vector<point> &serialRes, int N);
void parallelSearch(vector<point> &points, vector<pair<point, point>> &procPoints, vector<point> &procRes, int N, int procNP);
void getRes(vector<point> &procRes, vector<point> &res, int N, int procNP);
void testRes(vector<point> &points, vector<point> &res, int N);

double triangleSqr(point A, point B, point C);
void printPairs(vector<pair<point, point>> &procPoints, int procNP);
void printRes(vector<point> &res);

int main(int argc, char* argv[])
{
    vector<point> points;
    vector<pair<point, point>> procPoints;
    vector<point> res, procRes; // vector of 3 result points
    int N, procNP;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &procNum);
    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);

    init(points, N, res, procPoints, procRes, procNP);
    dataDist(points, procPoints, N, procNP);
    testDist(points, procPoints, N, procNP);
    parallelSearch(points, procPoints, procRes, N, procNP);
    getRes(procRes, res, N, procNP);
    cout<<"k";
    //testRes(points, res, N);
/*
    if (procRank == 0) {
        printRes(res);
    }*/
    //term(pMatrix, pVector, pResult, pProcRows, pProcResult);
    MPI_Finalize();
    return 0;
}

void init(vector<point> &points, int& N, vector<point> &res, vector<pair<point,point>> &procPoints, vector<point> &procRes, int& procNP) {
    if (procRank == 0) {
        freopen("in.txt","r", stdin);
        cin >> N;
        double x, y;
        for (int i=0; i<N; i++){
            if (cin >> x >> y)
                points.push_back(point(x, y));
        }
    }
    MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Datatype mpi_point;
    MPI_Type_contiguous(2, MPI_DOUBLE, &mpi_point);
    MPI_Type_commit(&mpi_point);

    MPI_Bcast(&points, N, mpi_point, 0, MPI_COMM_WORLD);

    // Determine the number of pair of points stored on each process
    int restNP = N*(N-1)/2;
    for (int i=0; i<procRank; i++)
        restNP = restNP - restNP/(procNum-i);
    procNP = restNP/(procNum - procRank);
}

void dataDist(vector<point> &points, vector<pair<point, point>> &procPoints, int N, int procNP) {
    int *pSendNum = new int [procNum];// the number of elements sent to the process
    int *pSendInd = new int [procNum]; // the index of the first data element sent to the process
    int restNP = N*(N-1)/2; // Number of rows, that haven’t been distributed yet

    restNP = N*(N-1)/2;
    procNP = restNP / procNum;
    pSendNum[0] = restNP;
    pSendInd[0] = 0;
    for (int i=1; i<procNum; i++) {
        restNP -= procNP;
        procNP = restNP/(procNum - i);
        pSendNum[i] = procNP;
        pSendInd[i] = pSendInd[i-1] + pSendNum[i-1];
    }


    vector<pair<point, point>> pairs;
    for (int i=0; i < N; i++){
        for (int j=i+1; j < N; j++) {
            pair <point, point> p = make_pair(points[i], points[j]);
            pairs.push_back(p);
        }
    }

    MPI_Datatype mpi_point_pair;
    MPI_Datatype mpi_point;
    MPI_Type_contiguous(2, MPI_DOUBLE, &mpi_point);
    MPI_Type_commit(&mpi_point);
    MPI_Type_contiguous(2, mpi_point, &mpi_point_pair);
    MPI_Type_commit(&mpi_point_pair);

    pair<point, point> *procP = new pair<point, point> [N*(N-1)/2];
    MPI_Scatterv(pairs.data(), pSendNum, pSendInd, mpi_point_pair, procP, pSendNum[procRank], mpi_point_pair, 0, MPI_COMM_WORLD);
    //MPI_Scatter(pairs.data(), pairs.size(), mpi_point_pair, procP, procNP, mpi_point_pair, 0, MPI_COMM_WORLD);
    for (int i=0; i< N*(N-1)/2 ;i++){
        procPoints.push_back(procP[i]);
    }

    delete [] pSendNum;
    delete [] pSendInd;
}

void testDist(vector<point> &points, vector<pair<point, point>> &procPoints, int N, int procNP) {
    MPI_Barrier(MPI_COMM_WORLD);
    for (int i=0; i<procNum; i++) {
        if (procRank == i) {
            printf("\nProcRank = %d \n", procRank);
            printPairs(procPoints, procNP);
        }
        MPI_Barrier(MPI_COMM_WORLD);
    }
}

void serialSearch(vector<point> &points, vector<point> &serialRes, int N) {
    int n = min(N, (int)points.size());
    double ans = 0, currS;
    for (int i = 0; i < n; i++){
        for (int j=i+1; j < n; j++){
            for (int k=j+1; k<n; k++){
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
}

double triangleSqr(point A, point B, point C) {
    double a = sqrt((C.x-B.x)*(C.x-B.x) + (C.y-B.y)*(C.y-B.y));
    double b = sqrt((A.x-C.x)*(A.x-C.x) + (A.y-C.y)*(A.y-C.y));
    double c = sqrt((A.x-B.x)*(A.x-B.x) + (A.y-B.y)*(A.y-B.y));
    double p = (a + b + c)/2;
    return sqrt(p*(p-a)*(p-b)*(p-c));
}

void printPairs(vector<pair<point, point>> &procPoints, int procNP) {
    for (int i=0; i<procNP; i++){
        printf("(%f; %f) (%f; %f)\n", procPoints[i].first.x, procPoints[i].first.y,
               procPoints[i].second.x, procPoints[i].second.y);
    }
}

void printRes(vector<point> &res) {
    for (int i=0; i< 3; i++)
        printf("(%f; %f)\n", res[i].x, res[i].y);
}

void parallelSearch(vector<point> &points, vector<pair<point, point>> &procPoints, vector<point> &procRes, int N, int procNP) {
    double ans = 0, currS;
    procRes.resize(3);
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
                cout << ans << endl;
            }
        }
    }
}
void getRes(vector<point> &procRes, vector<point> &res, int N, int procNP) {
    int restNP = N*(N-1)/2; // Number of rows, that haven’t been distributed yet
    int* pReceiveNum = new int [procNum];
    int* pReceiveInd = new int [procNum];
    pReceiveInd[0] = 0;
    pReceiveNum[0] = N*(N-1)/2/procNum;
    for (int i=1; i<procNum; i++) {
        restNP -= pReceiveNum[i-1];
        pReceiveNum[i] = restNP/(procNum-i);
        pReceiveInd[i] = pReceiveInd[i-1] + pReceiveNum[i-1];
    }

    MPI_Datatype mpi_point_pair;
    MPI_Datatype mpi_point;
    MPI_Type_contiguous(2, MPI_DOUBLE, &mpi_point);
    MPI_Type_commit(&mpi_point);
    MPI_Type_contiguous(2, mpi_point, &mpi_point_pair);
    MPI_Type_commit(&mpi_point_pair);

    point *pRes = new point [3];
    cout <<"h\n";
    MPI_Allgatherv(procRes.data(), pReceiveNum[procRank], mpi_point, pRes, pReceiveNum, pReceiveInd, mpi_point, MPI_COMM_WORLD);
    cout <<"h\n";
    for (int i=0; i< 3 ;i++){
        cout << pRes[i].x << ' ';
        res.push_back(pRes[i]);
    }
    // Free the memory
    delete [] pReceiveNum;
    delete [] pReceiveInd;
}

void testRes(vector<point> &points, vector<point> &res, int N) {
    if (procRank == 0){
        vector<point> serialRes;
        serialSearch(points, serialRes, N);
        for (int i=0; i<res.size(); i++){
            cout << i;
        }
    }

}
/*

void testRes(double* pMatrix, double* pVector, double* pResult, int rowSize, int colSize) {
    if (procRank == 0) {
        double* pSerialResult = calc(pMatrix, pVector, rowSize, colSize);
        for (int i=0; i<rowSize; i++) {
            if (pResult[i] != pSerialResult[i]) {
                printf("The results of serial and parallel algorithms are NOT identical.\n\n");
                return;
            }
        }
        printf("The results of serial and parallel algorithms are identical.\n");
        delete [] pSerialResult;
    }
}

double* calc(double* pMatrix, double* pVector, int rowSize, int colSize) {
    double* ans = new double[rowSize];
    for (int i=0; i<rowSize; i++) {
        ans[i] = 0;
        for (int j=0; j<colSize; j++) {
            ans[i] += pMatrix[i*colSize+j] * pVector[j];
        }
    }
    return ans;
}*/
