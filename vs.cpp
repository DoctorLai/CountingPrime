#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include <math.h>
#include <ppl.h>

using namespace std;

const int MAXN = 10000000;

int IsPrime(int number)
{
	if (number <= 1) return 0;
	int right = (int)floor(sqrt(number));
	for (int index = 2; index <= right; ++index)
		if (number % index == 0)
			return 0;
	return 1;
}

int Single(int n) {
	int s = 0;
	for (int i = 1; i <= n; ++i) {
		if (IsPrime(i)) {
			++s;
		}
	}
	return s;
}

int Parallel1(int n) {
	volatile long s = 0;
	Concurrency::parallel_for(0, n, [&](int i) {
		if (IsPrime(i)) {
			InterlockedIncrement(&s);
		}
	});
	return s;
}

int Parallel2(int n) {
	volatile long s = 0;
	Concurrency::parallel_for(0, n, [&](int i) {
		InterlockedAdd(&s, IsPrime(i));
	});
	return s;
}

int main() {
	DWORD serial, parallel1, parallel2, s;
	DWORD startTime = GetTickCount();
	s = Single(MAXN);
	cout << s << endl;
	serial = GetTickCount() - startTime;

	startTime = GetTickCount();
	s = Parallel1(MAXN);
	parallel1 = GetTickCount() - startTime;
	cout << s << endl;

	startTime = GetTickCount();
	s = Parallel2(MAXN);
	parallel2 = GetTickCount() - startTime;
	cout << s << endl;

	cout << "Serial = " << serial << endl;
	cout << "Parallel1 = " << parallel1 << endl;
	cout << "Parallel2 = " << parallel2 << endl;

	return 0;
}
