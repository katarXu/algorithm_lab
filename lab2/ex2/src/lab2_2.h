#pragma once
#include"Complex.h"
#include<Windows.h>
#include<fstream>

complex *FFT(complex a[], int n) {
	if (n == 1)
		return a;
	complex w(1, 0);
	complex wn(1, 2 * PI / n, 1);
	//complex *a0 = new complex[n / 2];
	//complex *a1 = new complex[n / 2];
	complex *y0 = new complex[n / 2];
	complex *y1 = new complex[n / 2];
	complex *y = new complex[n];
	for (int i = 0; i < n; i += 2) {
		y0[i / 2] = a[i];
		y1[i / 2] = a[i + 1];
	}
	y0 = FFT(y0, n / 2);
	y1 = FFT(y1, n / 2);
	for (int i = 0; i < n / 2; ++i) {
		y[i] = y0[i] + w * y1[i];
		y[i + n / 2] = y0[i] - w * y1[i];
		w = w * wn;
	}
	delete[] y0;
	delete[] y1;
	//delete[] a0;
	//delete[] a1;
	return y;
}

template<typename T>
void bitReverse(T a[], T b[], int n) {
	for (int i = 0, j = n - 1; i != n; ++i) {
		for (int l = n >> 1; (j ^= l) < l; l >>= 1)
			int a = i + 1;
		b[j] = a[i];
	}
}

complex *FFT1(complex a[], int n) {
	complex *y = new complex[n];
	bitReverse(a, y, n);
	for (int i = 2; i <= n; i <<= 1) {
		int m = i >> 1;
		complex wn(1, 2 * PI / i, 1);
		for (int j = 0; j != n; j += i) {
			complex w(1, 0);
			for (int k = 0; k != m; ++k) {
				complex t = w * y[j + k + m];
				y[j + k + m] = y[j + k] - t;
				y[j + k] = y[j + k] + t;
				w = w * wn;
			}
		}
	}
	return y;
}

complex *coefficient(complex *y, int n) {
	complex *a = new complex[n];
	complex wn(1, 2 * PI / n, 1);
	for (int i = 0; i < n; ++i) {
		a[i] = complex(0, 0);
		for (int j = 0; j < n; ++j)
			a[i] = a[i] + y[j] * wn.pow(-i * j);
		a[i] = a[i] / n;
	}
	return a;
}

complex *multipoly(complex a[], complex b[], int n) {
	complex *ya = new complex[n];
	complex *yb = new complex[n];
	complex *y = new complex[2 * n - 1];
	ya = FFT(a, n);
	yb = FFT(b, n);
	delete[] ya;
	delete[] yb;
	return y;
}

template<typename T>
complex *init(T a[], int n) {
	complex *temp = new complex[n];
	for (int i = 0; i < n; ++i) 
		temp[i] = complex(a[i]);
	return temp;
}


double testTime(complex *(*fun)(complex*, int), complex a[], complex *&b, int n) {
	LARGE_INTEGER t1, t2, tc;
	QueryPerformanceFrequency(&tc);
	QueryPerformanceCounter(&t1);
	b = fun(a, n);
	QueryPerformanceCounter(&t2);
	return (t2.QuadPart - t1.QuadPart)*1.0 / tc.QuadPart;
}

template<typename T>
void Dispatch(std::istream& is, std::ostream& os, std::ostream& time) {
	int n = 0;
	while (is >> n) {
		double mtime = 0;
		T *a = new T[n];
		for (int i = 0; i < n; ++i)
			is >> a[i];
		complex *ca = init(a, n);
		complex *aa = nullptr;
		mtime = testTime(FFT1, ca, aa, n);
		time << mtime << endl;
		if (&os == &cout)
			cout << "dispatch n = " << n << endl;
		for (int i = 0; i < n; ++i)
			os << aa[i].re << ' ';
		if (&os == &cout)
			cout << endl;
		os << endl;
		delete[] a;
		delete[] ca;
		delete[] aa;
	}
}

