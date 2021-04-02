#include <iostream>
#include "windows.h"
#include "process.h"
#include<thread>
#include<chrono>
using namespace std;

CRITICAL_SECTION section;
int shared = 0;
int increments_per_thread = 1000;

void incrementCritical(void*){
	EnterCriticalSection(&section);
	for (int x=0;x<increments_per_thread; x++)
        shared+=1;
    cout << shared << endl;
	Sleep(1000);
	LeaveCriticalSection(&section);
	_endthread();
}

void increment(){
    for (int x=0;x<increments_per_thread; x++)
        shared+=1;
    cout << shared<<endl;
}
int main()
{
    auto start = chrono::high_resolution_clock::now();
    InitializeCriticalSection(&section);
    if (_beginthread(incrementCritical,1024,NULL)==-1)
		cout << "Error begin thread " << endl;
	if (_beginthread(incrementCritical, 1024,NULL)==-1)
		cout << "Error begin thread " << endl;
	Sleep(2000);
	chrono::seconds sec(2);
    auto finish = chrono::high_resolution_clock::now();
    cout << "Value " << shared << "\nTime " << chrono::duration_cast<chrono::microseconds>(finish-start-sec).count()<<endl;

	shared = 0;
	start = chrono::high_resolution_clock::now();
	thread t0, t1;
	t0 = thread(increment);
	t1 = thread(increment);
	t0.join();
	t1.join();
	finish = chrono::high_resolution_clock::now();
	cout << "Value " << shared << "\nTime " << chrono::duration_cast<chrono::microseconds>(finish-start).count()<<endl;
	return 0;
}
