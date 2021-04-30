#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

int n = 1000;
double cos(double x, int n) {
    double part = 1;
    double sum = part;
    for (int i = 1; i <= n; i ++){
        part *= (x / (2*i) * x / (2*i-1));
        part *= -1;
        sum += part;

    }
    return sum;
}

double sin(double x, int n) {
    double part = x;
    double sum = part;
    for (int i = 1; i <= n; i ++){
        part *= (x / (2*i) * x / (2*i+1));
        part *= -1;
        sum += part;

    }
    return sum;
}

double sh(double x, int n){
    double part = x;
    double sum = part;
    for (int i = 1; i <= n; i ++){
        part *= (x*x / (2*i+1)/(2*i));
        sum += part;
    }
    return sum;
}

double ch(double x, int n) {
    double part = 1;
    double sum = part;
    for (int i = 1; i <= n; i ++){
        part *= (x*x / (2*i)/(2*i-1));
        sum += part;
    }
    return sum;
}


int main()
{
    double x;
    for (int i=0; i <10; i++){
    cout << "Input x and N or skip: ";
    cin >> x >> n;
    cout << "x="<<x<<" n="<<n<<endl;
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    printf("serial sin %f = %.20f\n", x, sin(x, n));
    printf("serial cos %f = %.20f\n", x, cos(x, n));
    printf("serial sh %f = %.20f\n", x, sh(x, n));
    printf("serial ch %f = %.20f\n", x, ch(x, n));
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
    std::cout << "Time of execution " << time_span.count() << " seconds.\n";
    }
    return 0;
}
