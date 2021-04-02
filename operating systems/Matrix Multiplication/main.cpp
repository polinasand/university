#include <iostream>
#include<chrono>
#include<thread>
#include<mutex>
using namespace std;

int **a, **b, **res;
int n, k, m;
mutex out;

int** init(int m, int n) {
    int **a = new int*[m];
    for (int i=0; i<m; i++){
        a[i] = new int[n];
    }
    return a;
}

void termination(int** a, int n){
    for (int i=0; i<n; i++)
        delete[] a[i];
    delete [] a;
}

void fillRandom(int** a, int m, int n){
    srand(time(nullptr));
    for (int i=0; i<m; i++){
        for (int j=0; j<n; j++){
            a[i][j] = rand() % 100;
        }
    }
}

// a[i][1...m] and b[1..m][j]
void vectorMult(int i, int j, bool p){
    int ans = 0;
    for (int l=0; l<m; l++){
        ans += a[i][l] * b[l][j];
        ans %= 1000;
    }
    res[i][j] = ans;
    if (p){
        out.lock();
        cout << i << ' ' << j << ' ' << ans<<endl;
        out.unlock();
    }
}

void serialMult(){
    cout << "started serial mult\n";
    for (int i=0; i<n; i++){
        for (int j=0; j<k; j++)
            vectorMult(i, j, false);
    }
}
void multithreadedMult(){
    cout << "started multithreaded mult\n";
    thread t[n*k];
    for (int i=0; i<n; i++){
        for (int j=0; j<k; j++){
            t[i*k+j] = thread(vectorMult, i, j, false);
        }
    }
    for (int i=0; i<n*k; i++)
        t[i].join();
}

void print(int **a, int m ,int n){
    for (int i=0; i<m; i++){
        for (int j=0; j<n; j++)
            cout <<a[i][j] << ' ';
        cout << endl;
    }

}
int main()
{
    cout << "Input n, m, k\n";
    cin>>n>>m>>k;
    a = init(n,m);
    b = init(m,k);
    res = init(n,k);
    fillRandom(a,n,m);
    fillRandom(b,m,k);
    auto start = chrono::high_resolution_clock::now();
    serialMult();
    auto finish = chrono::high_resolution_clock::now();
    cout << "Time of execution "<<chrono::duration_cast<chrono::microseconds>(finish-start).count() << "ms\n";
   // print(res, n, k);
    start = chrono::high_resolution_clock::now();
    multithreadedMult();
    finish = chrono::high_resolution_clock::now();
    cout << "Time of execution "<<chrono::duration_cast<chrono::microseconds>(finish-start).count() << "ms\n";
    //print(res, n ,k);
    termination(a, n);
    termination(b, m);
    termination(res, n);
    return 0;
}
