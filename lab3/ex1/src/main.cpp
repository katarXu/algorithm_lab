#include<iostream>
#include<cstdlib>
#include<ctime>
#include"lab3_1.h"

#define N 100

int main() {
	srand(time(NULL));
	std::ofstream ofp("../input/input.txt", std::ios::out | std::ios::trunc);
	if (!ofp) {
		std::cout << "Cannot open the target file1\n";
		system("pause");
		return 0;
	}
	for (int i = 0; i < N; ++i)
		ofp << rand(32768) << ' ';
	ofp.close();

	
	std::ofstream ofInorder("../output/inorder.txt", std::ios::out | std::ios::trunc);
	std::ofstream ofTime1("../output/time1.txt", std::ios::out | std::ios::trunc);
	std::ofstream ofDelete("../output/delete_data.txt", std::ios::out | std::ios::trunc);
	std::ofstream ofTime2("../output/time2.txt", std::ios::out | std::ios::trunc);
	if (!ofInorder||!ofTime1||!ofDelete||!ofTime2) {
		std::cout << "Cannot open the target file2\n";
		system("pause");
		return 0;
	}

	int size[] = { 20,40,60,80,100 };
	for (int i = 0; i < sizeof(size) / sizeof(int); ++i) {
		std::ifstream ifp("../input/input.txt", std::ios::in);
		if (!ifp) {
			std::cout << "Cannot open the target file1\n";
			system("pause");
			return 0;
		}
		node root = initRBT(size[i], ifp, ofInorder, ofDelete, ofTime1, ofTime2);
		ifp.close();
		delete[] root;
	}

	ofInorder.close();
	ofTime1.close();
	ofTime2.close();
	ofDelete.close();
	system("pause");
}