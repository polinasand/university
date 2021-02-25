#include <iostream>
#include <mpi.h>
#include <string>
#include <conio.h>
#include <time.h>
using namespace std;

int procNum; // Number of available processes
int procRank; // Rank of current process

void init(double* &pMatrix, double* &pVector, double* &pResult, double* &pProcRows, double* &pProcResult, int &rowSize, int& colSize, int &rowNum);
void randomInit(double* &pMatrix, double* &pVector, int rowSize, int colSize);
void term(double* pMatrix, double* pVector, double* pResult, double* pProcRows, double* pProcResult);
void printMatrix(double*, int, int);
void printVector(double*, int);
void dataDist(double* pMatrix, double* pProcRows, double* pVector, int rowSize, int colSize, int rowNum);
void testDist(double* pMatrix, double* pVector, double* pProcRows, int rowSize, int colSize, int rowNum);
double* calc(double* pMatrix, double* pVector, int rowSize, int colSize);
void parallelCalc(double* pProcRows, double* pVector, double* pProcResult, int rowSize, int colSize, int rowNum);
void testCalc(double* pProcResult, int rowNum);
void res(double* pProcResult, double* pResult, int rowSize, int colSize, int rowNum);
void testRes(double* pMatrix, double* pVector, double* pResult, int rowSize, int colSize);

int main(int argc, char* argv[])
{
    printf("\nSerial matrix-vector multiplication program\n");
    double* pMatrix;
    double* pVector;
    double* pResult;
    int rowSize, colSize;
    double* pProcRows;
    double* pProcResult;
    int rowNum;
    //double* pSerialResult;
    double s, f;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &procNum);
    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
    init(pMatrix, pVector, pResult, pProcRows, pProcResult, rowSize, colSize, rowNum);
    s = clock();
    dataDist(pMatrix, pProcRows, pVector, rowSize, colSize, rowNum);
    //testDist(pMatrix, pVector, pProcRows, rowSize, colSize, rowNum);
    parallelCalc(pProcRows, pVector, pProcResult, rowSize, colSize, rowNum);
    //testCalc(pProcResult, rowNum);
    res(pProcResult, pResult, rowSize, colSize, rowNum);
    f = clock();

    testRes(pMatrix, pVector, pResult, rowSize, colSize);

    if (procRank == 0) {
        printf("Time of execution = %f\n", (f-s) / (double)CLOCKS_PER_SEC);
        printVector(pResult, rowSize);
    }
    term(pMatrix, pVector, pResult, pProcRows, pProcResult);
    MPI_Finalize();
    return 0;
}

void init(double* &pMatrix, double* &pVector, double* &pResult, double* &pProcRows, double* &pProcResult, int &rowSize, int& colSize, int &rowNum) {
    if (procRank == 0) {
        scanf("%d", &rowSize);
        scanf("%d", &colSize);
        while (rowSize <= 0 || colSize <= 0){
            printf("\nSize of objects must be greater than 0!\n");
            scanf("%d", &rowSize);
            scanf("%d", &colSize);
        }
    }
    MPI_Bcast(&rowSize, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&colSize, 1, MPI_INT, 0, MPI_COMM_WORLD);
    printf("Chosen objects sizes = %d %d\n", rowSize, colSize);
    // Determine the number of matrix rows stored on each process
    int restRows = rowSize;
    for (int i=0; i<procRank; i++)
        restRows = restRows - restRows/(procNum-i);
    rowNum = restRows/(procNum - procRank);
    pProcRows = new double [rowNum*colSize];
    pProcResult = new double [rowNum];
    pVector = new double[colSize];
    pResult = new double[rowSize];

    if (procRank == 0) {
        randomInit(pMatrix, pVector, rowSize, colSize);
    }

}

void randomInit(double* &pMatrix, double* &pVector, int rowSize, int colSize) {
    for (int i=0; i<colSize; i++) {
            pVector[i] = (rand() % 100) * (rand() % 2 ? 1 : -1);
        }
        pMatrix = new double [rowSize*colSize];
        for (int i = 0; i<rowSize; i++) {
            for (int j=0; j<colSize; j++) {
                pMatrix[i*colSize + j] = (rand() % 100) * (rand() % 2 ? 1 : -1);
            }
        }
}

void printMatrix(double* matrix, int rowSize, int colSize) {
    for (int i = 0; i<rowSize; i++) {
        for (int j=0; j<colSize; j++)
            printf("%7.4f ", matrix[i*colSize+j]);
        printf("\n");
    }
}

void printVector(double* p, int Size) {
    for (int i=0; i<Size; i++)
        printf("%7.4f ", p[i]);
    printf("\n");
}

void term(double* pMatrix, double* pVector, double* pResult, double* pProcRows, double* pProcResult) {
    delete [] pMatrix;
    delete [] pVector;
    delete [] pResult;
    delete [] pProcRows;
    delete [] pProcResult;
}

void dataDist(double* pMatrix, double* pProcRows, double* pVector, int rowSize, int colSize, int rowNum) {
    int *pSendNum = new int [procNum];// the number of elements sent to the process
    int *pSendInd = new int [procNum]; // the index of the first data element sent to the process
    int restRows = rowSize; // Number of rows, that haven’t been distributed yet
    MPI_Bcast(pVector, colSize, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    rowNum = rowSize / procNum;
    pSendNum[0] = rowNum*colSize;
    pSendInd[0] = 0;
    for (int i=1; i<procNum; i++) {
        restRows -= rowNum;
        rowNum = restRows/(procNum-i);
        pSendNum[i] = rowNum*colSize;
        pSendInd[i] = pSendInd[i-1] + pSendNum[i-1];
    }
    MPI_Scatterv(pMatrix, pSendNum, pSendInd, MPI_DOUBLE, pProcRows, pSendNum[procRank], MPI_DOUBLE, 0, MPI_COMM_WORLD);
    delete [] pSendNum;
    delete [] pSendInd;
}

void testDist(double* pMatrix, double* pVector, double* pProcRows, int rowSize, int colSize, int rowNum) {
    if (procRank == 0) {
        printf("Initial Matrix: \n");
        printMatrix(pMatrix, rowSize, colSize);
        printf("Initial Vector: \n");
        printVector(pVector, colSize);
    }
    MPI_Barrier(MPI_COMM_WORLD);
    for (int i=0; i<procNum; i++) {
        if (procRank == i) {
            printf("\nProcRank = %d \n", procRank);
            printf(" Matrix Stripe:\n");
            printMatrix(pProcRows, rowNum, colSize);
            printf(" Vector: \n");
            printVector(pVector, colSize);
        }
        MPI_Barrier(MPI_COMM_WORLD);
    }
}

void parallelCalc(double* pProcRows, double* pVector, double* pProcResult, int rowSize, int colSize, int rowNum) {
    for (int i=0; i<rowNum; i++) {
        pProcResult[i] = 0;
        for (int j=0; j<colSize; j++) {
            pProcResult[i] += pProcRows[i*colSize+j] * pVector[j];
        }
    }
}

void testCalc(double* pProcResult, int rowNum) {
    for (int i=0; i<procNum; i++) {
        if (procRank == i) {
            printf("ProcRank = %d \n", procRank);
            printf("Part of result vector: \n");
            printVector(pProcResult, rowNum);
        }
        MPI_Barrier(MPI_COMM_WORLD);
    }
}

void res(double* pProcResult, double* pResult, int rowSize, int colSize, int rowNum) {
    int *pReceiveNum; // Number of elements, that current process sends
    int *pReceiveInd; /* Index of the first element from current process in result vector */
    int restRows = rowSize; // Number of rows, that haven’t been distributed yet
    pReceiveNum = new int [procNum];
    pReceiveInd = new int [procNum];
    pReceiveInd[0] = 0;
    pReceiveNum[0] = rowSize/procNum;
    for (int i=1; i<procNum; i++) {
        restRows -= pReceiveNum[i-1];
        pReceiveNum[i] = restRows/(procNum-i);
        pReceiveInd[i] = pReceiveInd[i-1] + pReceiveNum[i-1];
    }
    MPI_Allgatherv(pProcResult, pReceiveNum[procRank], MPI_DOUBLE, pResult,
    pReceiveNum, pReceiveInd, MPI_DOUBLE, MPI_COMM_WORLD);
    // Free the memory
    delete [] pReceiveNum;
    delete [] pReceiveInd;
}

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
}
