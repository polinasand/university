#include <iostream>
#include <omp.h>
#include <cmath>
#include <chrono>
using namespace std::chrono;

int THREAD_NUM = 4;

using namespace std;

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
int main(int argc, char** argv) {
    double x;
    int n;
    cout << "Input thread nums:";
    cin >> THREAD_NUM;
    cout << "Input x and n:";
    cin >> x >> n;
    double sum_sin=0, sum_cos=0, sum_sh=0, sum_ch=0, part_sin, part_cos, part_sh, part_ch;
    omp_set_num_threads(THREAD_NUM);
    int num_per_thread = ceil(n / THREAD_NUM);
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
#pragma omp parallel for
    for ( int k=0; k<THREAD_NUM; k++) {
        part_sin = sin(x, k*num_per_thread, min(n, (k+1)*num_per_thread));
        part_cos = cos(x, k*num_per_thread, min(n, (k+1)*num_per_thread));
        part_sh = sh(x, k*num_per_thread, min(n, (k+1)*num_per_thread));
        part_ch = ch(x, k*num_per_thread, min(n, (k+1)*num_per_thread));
#pragma omp critical
        sum_sin += part_sin;
        sum_cos += part_cos;
        sum_sh += part_sh;
        sum_ch += part_ch;
    }

    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(t2 - t1);

    std::cout << "Time of execution " << time_span.count() << " seconds.\n";
    printf("sin %f = %.20f\n", x, sum_sin);
    printf("cos %f = %.20f\n", x, sum_cos);
    printf("sh %f = %.20f\n", x, sum_sh);
    printf("ch %f = %.20f\n", x, sum_ch);
    return 0;
}