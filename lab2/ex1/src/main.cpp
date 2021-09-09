#include"lab2_1.h"


int main() {
	std::ifstream ifp("../input/2_1_input.txt", std::ios::in);
	if (!ifp) {
		std::cout << "Cannot open the target file1\n";
		system("pause");
		return 0;
	}
	std::ofstream ofp1("../output/result.txt", std::ios::out | std::ios::trunc);
	std::ofstream ofp2("../output/time.txt", std::ios::out | std::ios::trunc);
	if (!ofp1 && !ofp2) {
		std::cout << "Cannot open the target file2\n";
		system("pause");
		return 0;
	}
	Dispatch<long long>(ifp, ofp1, ofp2);
	ifp.close();
	ofp1.close();
	ofp2.close();
	system("pause");
}