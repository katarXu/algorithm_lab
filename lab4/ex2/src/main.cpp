#include"lab4_2.h"

int main(){
	srand(time(NULL));
	ofstream ofp1, ofp2, ofp3;
	string a = "../input/input00.txt";
	string b = "../output/result00.txt";
	int size[] = { 27,81,243,729 };
	double t1, t2;
	ofp3.open("../output/time.txt", std::ios::out | std::ios::trunc);
	for (int i = 0; i < sizeof(size) / sizeof(int); ++i) {
		a[14] = '0' + i + 1;
		a[15] = '1';
		b[16] = '0' + i + 1;
		b[17] = '1';
		ofp1.open(a, std::ios::out | std::ios::trunc);
		ofp2.open(b, std::ios::out | std::ios::trunc);
		t1 = test(size[i], 5, ofp1, ofp2);
		ofp1.close();
		ofp2.close();

		a[15] = '2';
		b[17] = '2';
		ofp1.open(a, std::ios::out | std::ios::trunc);
		ofp2.open(b, std::ios::out | std::ios::trunc);
		t2 = test(size[i], 7, ofp1, ofp2);
		ofp1.close();
		ofp2.close();

		ofp3 << size[i] << '\t' << t1 << '\t' << t2 << endl;
	}
	system("pause");
	return 0;
}