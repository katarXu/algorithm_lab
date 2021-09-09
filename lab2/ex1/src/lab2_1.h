#pragma once
#include<iostream>
#include<cstdlib>
#include<fstream>
#include<Windows.h>

#define INF 0x3f3f3f3f
#define LINF 0x3f3f3f3f3f3f3f3f
using std::cout;
using std::cin;
using std::endl;

template<typename T>
void ChainOrder(T *p, T **cost, int **cut, int length) {
	if (length < 2) {
		//std::cout << "array too short\n";
		//system("pause");
		exit(1);
	}
	int n = length - 1;
	for (int l = 2; l <= n; ++l) {
		for (int i = 1; i <= n - l + 1; ++i) {
			int j = i + l - 1;
			cost[i][j] = LINF;
			for (int k = i; k < j; ++k) {
				T q = cost[i][k] + cost[k + 1][j] + p[i - 1] * p[k] * p[j];
				if (q < cost[i][j]) {
					cost[i][j] = q;
					cut[i][j] = k;
				}
			}
		}
	}
}

void CutPlan(int **cut, int start, int end, std::ostream& os = cout) {
	if (start > end)
		return;
	if (start == end)
		os << 'A' << start;
	else {
		os << "(";
		CutPlan(cut, start, cut[start][end], os);
		CutPlan(cut, cut[start][end] + 1, end, os);
		os << ")";
	}
}

template<typename T>
void printArray(T **arr, int a, int b, std::ostream& os = cout) {
	for (int i = 0; i < a; ++i) {
		for (int j = 0; j < b; ++j)
			os << arr[i][j] << ' ';
		os << endl;
	}
}

template<typename T>
double testTime(void (*fun)(T*, T**, int**, int), T p[], T **cost, int **cut, int length) {
	LARGE_INTEGER t1, t2, tc;
	QueryPerformanceFrequency(&tc);
	QueryPerformanceCounter(&t1);
	fun(p, cost, cut, length);
	QueryPerformanceCounter(&t2);
	return (t2.QuadPart - t1.QuadPart)*1.0 / tc.QuadPart;
}


template<typename T>
void Dispatch(std::istream& is, std::ostream& os, std::ostream& time) {
	int n = 0;
	while (is >> n) {
		double mtime = 0;
		++n;
		T *a = new T[n];
		T **cost = new T*[n];
		int **cut = new int*[n];
		for (int i = 0; i < n; ++i)
			is >> a[i];
		for (int i = 0; i < n; ++i) {
			cost[i] = new T[n] {};
			cut[i] = new int[n] {};
		}
		mtime = testTime(ChainOrder, a, cost, cut, n);
		time << mtime << endl;
		if (&os == &cout)
			cout << "dispatch n = " << n - 1 << endl;
		//printArray(cost, n, n);
		//printArray(cut, n, n);
		os << cost[1][n - 1] << endl;
		CutPlan(cut, 1, n - 1, os);
		if (&os == &cout)
			cout << endl;
		os << endl;
		delete[] a;
		delete[] cost;
		delete[] cut;
	}
}