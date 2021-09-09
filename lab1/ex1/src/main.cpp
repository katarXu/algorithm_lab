#include"lab1.h"
#include<Windows.h>

int main() {

	for (int i = 1; i <= 5; ++i) {
		if (EOF == remove(("../output/" + str[i - 1] + "/time.txt").data())) {
			std::cout << "Remove " << "../output/" + str[i - 1] + "/time.txt" << " Error\n";
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
	*/

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
		*/

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

/*

*/