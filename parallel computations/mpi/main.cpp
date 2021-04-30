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

double cos(double x, int nbegin, int nend) {
    double part = 1;
    double sum = part;
    for (int i = nbegin+1; i <= nend; i ++){
        part *= (x / (2*i) * x / (2*i-1));
        part *= -1;
        sum += part;
    }
    return sum;
}

double sin(double x, int nbegin, int nend) {
    double part = x;
    double sum = part;
    for (int i = nbegin+1; i <= nend; i ++){
        part *= (x / (2*i) * x / (2*i+1));
        part *= -1;
        sum += part;

    }
    return sum;
}

double sh(double x, int nbegin, int nend) {
    double part = x;
    double sum = part;
    for (int i = nbegin+1; i <= nend; i ++){
        part *= (x*x / (2*i+1)/(2*i));
        sum += part;
    }
    return sum;
}

double ch(double x, int nbegin, int nend) {
    double part = 1;
    double sum = part;
    for (int i = nbegin+1; i <= nend; i ++){
        part *= (x*x / (2*i)/(2*i-1));
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
        double start = MPI_Wtime();
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

        double ans_sin = sin(x, 0, n / np);
        double ans_cos = cos(x, 0, n / np);
        double ans_sh = sh(x, 0, n / np);
        double ans_ch = ch(x, 0, n / np);
        // collects partial sums from other processes
        double tmp[4];
        for (int i = 1; i < np; i++) {
            MPI_Recv(&tmp[0], 4, MPI_DOUBLE, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD,&status);
            ans_sin += tmp[0];
            ans_cos += tmp[1];
            ans_sh += tmp[2];
            ans_ch += tmp[3];
        }
        double finish = MPI_Wtime();
        // prints the final sum of array
        printf("parallel sin %f = %.20f\n", x, ans_sin);
        printf("parallel cos %f = %.20f\n", x, ans_cos);
        printf("parallel sh %f = %.20f\n", x, ans_sh);
        printf("parallel ch %f = %.20f\n", x, ans_ch);
        printf("Time of execution = %f\n", finish-start);

    }
    // slave processes
    else {
        MPI_Recv(&xr, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &status);
        MPI_Recv(&nbegin, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        MPI_Recv(&nend, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

        // calculates its partial sum
        double partial_sin = sin(xr, nbegin, nend);
        double partial_cos = cos(xr, nbegin, nend);
        double partial_sh = sh(xr, nbegin, nend);
        double partial_ch = ch(xr, nbegin, nend);
        double partial[4] = {partial_sin, partial_cos, partial_sh, partial_ch};
        // sends the partial sum to the root process
        MPI_Send(&partial[0], 4, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
