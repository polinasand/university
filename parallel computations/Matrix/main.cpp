#include <iostream>
#include <mpi.h>
#include <string>
#include <conio.h>
using namespace std;

int procNum = 0; // Number of available processes
int procRank = 0; // Rank of current process
double* pProcRows;
double* pProcResult;
int rowNum;

double* pMatrix;
double* pVector;
double* pResult;
int colSize = 0;
int rowSize = 0;

void init();
void randomInit();
void term();
void printMatrix(double*, int, int);
void printVector(double*, int);
void dataDist();
void testDist();
double* calc();
void parallelCalc();
void testCalc();
void res();
void testRes();

int main(int argc, char* argv[])
{
    printf("Serial matrix-vector multiplication program\n");
    //getch();
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &procNum);
    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
    init();
    dataDist();
    testDist();
    parallelCalc();
    testCalc();
    res();
    testRes();
    term();
    MPI_Finalize();
    return 0;
}

void init() {
    if (procRank == 0) {
        do {
            printf("\nEnter size of the matrix: ");
            scanf("%d", &rowSize);
            scanf("%d", &colSize);
            if (rowSize <= 0 || colSize <= 0)
                printf("\nSize of objects must be greater than 0!\n");
        } while (rowSize <= 0 || colSize <= 0);
    }
    //send to process
    MPI_Bcast(&rowSize, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&colSize, 1, MPI_INT, 0, MPI_COMM_WORLD);
    printf("\nChosen objects sizes = %d %d", rowSize, colSize);
    printf("\n");
    // Determine the number of matrix rows stored on each process
    rowNum = rowSize/procNum;
    // Memory allocation
    pProcRows = new double [rowNum*colSize];
    pProcResult = new double [rowNum];
    pVector = new double [colSize];
    pResult = new double [rowSize];

    if (procRank == 0) {
        randomInit();
    }

}

void randomInit() {
    for (int i=0; i<colSize; i++) {
            pVector[i] = (i*i) %colSize;
        }
        pMatrix = new double [rowSize*colSize];
        // dummy init
        for (int i = 0; i<rowSize; i++) {
            for (int j=0; j<colSize; j++) {
                pMatrix[i*colSize + j] = (double)i*j + j;
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

void term() {
    delete [] pMatrix;
    delete [] pVector;
    delete [] pResult;
    delete [] pProcRows;
    delete [] pProcResult;
}

void dataDist() {
    MPI_Bcast(pVector, colSize, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Scatter(pMatrix, rowNum*colSize, MPI_DOUBLE, pProcRows, rowNum*colSize, MPI_DOUBLE, 0, MPI_COMM_WORLD);
}

void testDist() {
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

void parallelCalc() {
    for (int i=0; i<rowNum; i++) {
        pProcResult[i] = 0;
        for (int j=0; j<colSize; j++) {
            pProcResult[i] += pProcRows[i*colSize+j] * pVector[j];
        }
    }
}

void testCalc() {
    for (int i=0; i<procNum; i++) {
        if (procRank == i) {
            printf("ProcRank = %d \n", procRank);
            printf("Part of result vector: \n");
            printVector(pProcResult, rowNum);
        }
        MPI_Barrier(MPI_COMM_WORLD);
    }
}

void res() {
    MPI_Allgather(pProcResult, rowNum, MPI_DOUBLE, pResult, rowNum, MPI_DOUBLE, MPI_COMM_WORLD);
}

void testRes() {
    if (procRank == 0) {
        double* pSerialResult = calc();
        for (int i=0; i<rowSize; i++) {
            if (pResult[i] != pSerialResult[i]) {
                printf("The results of serial and parallel algorithms are NOT identical.\n");
                return;
            }
        }
        printf("The results of serial and parallel algorithms are identical.\n");
        delete [] pSerialResult;
    }
}

double* calc() {
    double* ans = new double[rowSize];
    for (int i=0; i<rowSize; i++) {
        ans[i] = 0;
        for (int j=0; j<colSize; j++) {
            ans[i] += pMatrix[i*colSize+j] * pVector[j];
        }
    }
    return ans;
}
