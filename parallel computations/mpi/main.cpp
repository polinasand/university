#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <cmath>
#include<iostream>
using namespace std;

int n = 20;
double x = 1, xr;
int pid, np;
int eps = 1e-30;

double process(double x, int nbegin, int nend) {
    double sum = 0;
    for (int i = nbegin; i < nend; i ++){
        double part = 1;
        int j = i;
        while (j>0){
            part *= (x / j);
            j--;
        }

        sum += part;

    }
    return sum;
}
double serial(double x){
    double sum=0;
    for (int i = 0; i < n; i ++){
        double part = 1;
        int j = i;
        while (j>0 && fabs(part) > eps){
            part *= (x / j);
            j--;
        }
        sum += part;
    }
    return sum;
}
int main(int argc, char* argv[])
{
    MPI_Status status;
    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &pid);
    MPI_Comm_size(MPI_COMM_WORLD, &np);

    int npp, nbegin, nend;
    // master process
    if (pid == 0) {
        cout << "Input x and N or skip: ";
        cin >> x >> n;
        cout << "x="<<x<<" n="<<n<<endl;
        npp = n / np;;
        int rest = n;
        nbegin = 0, nend = npp;
        if (np > 1) {
            for (int i = 1; i < np; i++) {
                // number of adds
                nbegin += npp;
                rest -= npp;
                npp = rest/(np-i);
                nend += npp;
                MPI_Send(&x, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
                MPI_Send(&nbegin, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
                MPI_Send(&nend, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            }
        }

        // master process part of calculating
        double start = MPI_Wtime();
        double ans = process(x, 0, n / np);
        // collects partial sums from other processes
        double tmp;
        for (int i = 1; i < np; i++) {
            MPI_Recv(&tmp, 1, MPI_DOUBLE, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD,&status);
            ans += tmp;
        }
        double finish = MPI_Wtime();
        // prints the final sum of array
        printf("parallel e^%f = %.20f\n", x, ans);
        printf("Time of execution = %f\n", finish-start);
        start = MPI_Wtime();
        printf("serial e^%f = %.20f\n", x, serial(x));
        finish = MPI_Wtime();
        printf("Time of execution = %f\n", finish-start);
        printf("math e^%f = %.20f\n", x, exp(x));


    }
    // slave processes
    else {
        MPI_Recv(&xr, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &status);
        MPI_Recv(&nbegin, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        MPI_Recv(&nend, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

        // calculates its partial sum
        double partial = process(xr, nbegin, nend);
        // sends the partial sum to the root process
        MPI_Send(&partial, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
