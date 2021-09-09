#pragma once
#include<iostream>
#include<time.h>
#include<stdlib.h>
#include<fstream>
#include<string>

#define INF 0xffff
#define PATTERN_NUM 5

std::string str[] = { "InsertSort","HeapSort","QuickSort","MergeSort","CountSort" };

template<typename T>
void ShowArray(T A[], int n) {
	//show the array A
	for (int i = 0; i < n; ++i)
		std::cout << A[i] << ' ';
	std::cout << std::endl;
}

void GenerateNum(std::ostream& ofp, int n) {
	//write N random numbers into ostream
	srand((unsigned)time(NULL)+52363221);
	while (n--)
		ofp << rand() << std::endl;
}

template<typename T>
void GetNum(std::istream& is, T A[]) {
	//read all numbers into A from istream
	int i = 0;
	while (!is.eof()) 
		is >> A[i++];
}

template<typename T>
void GetNum(std::istream& is, T A[], int n) {
	//read N numbers into A from istream
	while (n--)
		is >> A[n];
}

template<typename T>
void SaveNum(std::ostream& os, T A[], int n) {
	//write N numbers from A into ostream
	for (int i = 0; i < n; ++i)
		os << A[i] << std::endl;
}

template<typename T>
void exchange(T A[], int i, int j) {
	//exchange A[i] and A[j]
	if (A[i] != A[j]) {
		A[i] ^= A[j];
		A[j] ^= A[i];
		A[i] ^= A[j];
	}
}

template<typename T>
void InsertSort(T A[], int n) {
	for (int j = 1; j < n; ++j) {
		T low = A[j];
		int i = j - 1;
		while (i >= 0 && A[i] > low) {
			A[i + 1] = A[i];
			--i;
		}
		A[i + 1] = low;
	}
}

template<typename T>
void merge(T A[], int p, int q, int r) {
	int n1 = q - p + 1;
	int n2 = r - q;
	int* L = new int[n1 + 1];
	int* R = new int[n2 + 1];
	for (int i = 0; i < n1; ++i)
		L[i] = A[p + i];
	for (int i = 0; i < n2; ++i)
		R[i] = A[q + i + 1];
	L[n1] = INF;
	R[n2] = INF;
	for (int i = 0, j = 0, k = p; k <= r; ++k) {
		if (L[i] < R[j])
			A[k] = L[i++];
		else
			A[k] = R[j++];
	}
	delete L;
	delete R;
}

template<typename T>
void MergeSort(T A[], int p, int r) {
	if (p < r) {
		int q = (p + r) / 2;
		MergeSort(A, p, q);
		MergeSort(A, q + 1, r);
		merge(A, p, q, r);
	}
}

template<typename T>
void MergeSort(T A[], int n) {
	MergeSort(A, 0, n - 1);
}

#define LEFT(i) (2*(i)+1)
#define RIGHT(i) (2*(i+1))
#define PARENT(i) ((i-1)/2)

template<typename T>
void MaxHeap(T A[], int n ,int i) {
	int l = LEFT(i), r = RIGHT(i), largest = 0;
	if (l < n && A[l] > A[i])
		largest = l;
	else
		largest = i;
	if (r < n && A[r] > A[largest])
		largest = r;
	if (largest != i) {
		exchange(A, i, largest);
		MaxHeap(A, n, largest);
	}
}

template<typename T>
void HeapSort(T A[], int n) {
	for (int i = n / 2 - 1; i >= 0; --i)
		MaxHeap(A, n, i);
	for (int i = n - 1; i > 0; --i) {
		exchange(A, 0, i);
		MaxHeap(A, i, 0);
	}
}

template<typename T>
int Patition(T A[], int p, int r) {
	srand((unsigned)time(NULL));
	int random = rand() % (r - p) + p;
	exchange(A, random, r);
	int i = p - 1;
	for (int j = p; j < r; ++j)
		if (A[j] < A[r])
			exchange(A, ++i, j);
	exchange(A, r, ++i);
	return i;
}

template<typename T>
void QuickSort(T A[], int p, int r) {
	if (p < r) {
		int i = Patition(A, p, r);
		QuickSort(A, p, i - 1);
		QuickSort(A, i + 1, r);
	}
}

template<typename T>
void QuickSort(T A[], int n) {
	QuickSort(A, 0, n - 1);
}

template<typename T>
void CountSort(T A[], int n, int length = RAND_MAX) {
	T *count = new int[length + 1];
	for (int i = 0; i <= length; ++i)
		count[i] = 0;
	for (int i = 0; i < n; ++i)
		count[A[i]] += 1;
	for (int i = 0, cur = 0; i <= length; ++i)
		if (count[i])
			for (int j = 0; j < count[i]; ++j)
				A[cur++] = i;
}

/*
#include"lab1.h"
#include<Windows.h>

int main() {

	for (int i = 1; i <= 5; ++i) {
		if (EOF == remove(("../output/" + str[i - 1] + "/time.txt").data())) {
			std::cout << "Remove Error\n";
			system("pause");
		}
	}

	std::ofstream ofp;
	ofp.open("../input/input.txt", std::ios::out | std::ios::trunc);
	if (ofp) {
		std::cout << "Generating the data...\n";
		GenerateNum(ofp, (1 << 18) + 10);
		std::cout << "Finish generating\n\n";
		ofp.close();
	}
	else {
		std::cout << "Cannot open the target file\n";
		system("pause");
	}
	//return 0;

	/*
	std::cout << "Choose the size of input data, based by the power of 2\n";
	std::cin >> n1;
	

for (int x = 3; x < 20; x += 3) {
	int n1 = 0, n = 0, mode = 0;

	n1 = x;
	n = 1 << n1;
	int *a = new int[n];
	std::ifstream ifp;
	ifp.open("../input/input.txt", std::ios::in);
	if (!ifp) {
		std::cout << "Cannot open the target file\n";
		system("pause");
		return 0;
	}
	GetNum(ifp, a, n);
	ifp.close();

	/*
	std::cout << "Choose the pattern for this sort\n";
	for (int i = 1; i <= PATTERN_NUM; ++i)
		std::cout << i << ". " + str[i - 1] + "\n";
	//system("pause");
	std::cin >> mode;
	

	LARGE_INTEGER t1, t2, tc;
	double cost = 0.0;
	QueryPerformanceFrequency(&tc);

	for (int y = 1; y <= 5; ++y) {
		mode = y;
		std::ofstream ofp, tofp;
		std::string ab = "../output/" + str[mode - 1] + "/result_" + std::to_string(n1) + ".txt";
		ofp.open("../output/" + str[mode - 1] + "/result_" + std::to_string(n1) + ".txt", std::ios::out | std::ios::trunc);
		tofp.open("../output/" + str[mode - 1] + "/time.txt", std::ios::out | std::ios::app);
		if (!ofp) {
			std::cout << "Cannot open the target file, path : " << ab << std::endl;
			system("pause");
			return 0;
		}

		std::cout << "Start " << str[y - 1] << " , the size is 2^" << x;
		QueryPerformanceCounter(&t1);

		switch (mode) {
		case 1:
			InsertSort(a, n);
			break;
		case 2:
			HeapSort(a, n);
			break;
		case 3:
			QuickSort(a, n);
			break;
		case 4:
			MergeSort(a, n);
			break;
		case 5:
			CountSort(a, n);
			break;
		default:
			std::cout << "Unexcepted input\n";
			system("pause");
			break;
		}

		QueryPerformanceCounter(&t2);
		cost = (t2.QuadPart - t1.QuadPart)*1.0 / tc.QuadPart;
		std::cout << "    \t\t Time is " << cost << "s" << std::endl;
		tofp << cost << std::endl;

		SaveNum(ofp, a, n);
		ofp.close();
		tofp.close();
	}

	delete[]a;
}
system("pause");
}

*/