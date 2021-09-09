#include<iostream>
#include<cstdlib>
#include<ctime>
#include"lab3_2.h"


int main() {
	srand(time(NULL));
	std::ofstream ofp("../input/input.txt", std::ios::out | std::ios::trunc);
	if (!ofp) {
		std::cout << "Cannot open the target file1\n";
		system("pause");
		return 0;
	}
	for (int i = 0, j = 0, n = 30; i < n; ++j) {
		if (rand(25 - 0 + 1 + 50 - 30 + 1 - j) < n - i) {
			if (j <= 25)
				ofp << j << ' ' << j + rand(25 - j + 1) << endl;
			else
				ofp << j + 4 << ' ' << j + 4 + rand(50 - j - 4 + 1) << endl;
			++i;
		}
	}
	ofp.close();

	std::ofstream ofInorder("../output/inorder.txt", std::ios::out | std::ios::trunc);
	std::ofstream ofDelete("../output/delete_data.txt", std::ios::out | std::ios::trunc);
	std::ofstream ofSearch("../output/search.txt", std::ios::out | std::ios::trunc);
	if (!ofInorder||!ofDelete||!ofSearch) {
		std::cout << "Cannot open the target file2\n";
		system("pause");
		return 0;
	}

	int size[] = { 30 };

	for (int i = 0; i < sizeof(size) / sizeof(int); ++i) {
		std::ifstream ifp("../input/input.txt", std::ios::in);
		if (!ifp) {
			std::cout << "Cannot open the target file1\n";
			system("pause");
			return 0;
		}
		node root = initRBT(size[i], ifp, ofInorder, ofDelete, ofSearch);
		ifp.close();
		delete[] root;
	}

	ofInorder.close();
	ofSearch.close();
	ofDelete.close();
	system("pause");
}