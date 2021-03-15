#include <iostream>
#include "Philosopher.h"
#include "Fork.h"
#include<thread>
using namespace std;
void addPhilosopher(Philosopher* philosopher, int t, int num);

int main()
{
    int n, t;
	cout << "Enter number of philosophers:\n";
	cin >> n;
    cout << "Enter execution time in ms:\n";
	cin >> t;

	Fork* forks[n];
	for (int i = 0; i < n; i++){
		forks[i] = new Fork(i);
	}
    Philosopher* philosophers[n];
	thread threads[n];

	for (int i = 0; i < n; i++){
		philosophers[i] = new Philosopher(forks[i], forks[(i + 1) % n]);
		threads[i] = thread(addPhilosopher, philosophers[i], t, i);
	}
	for (int i = 0; i < n; i++){
		threads[i].join();
	}
	for (int i = 0; i < n; i++){
		cout << "Philosopher " << i << " ate for " <<
					 philosophers[i]->getEatingTime() <<" ms \n";
	}
    return 0;
}

void addPhilosopher(Philosopher* philosopher, int t, int num) {
	philosopher->start(chrono::milliseconds(t), num);
}
