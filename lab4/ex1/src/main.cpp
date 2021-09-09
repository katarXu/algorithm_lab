#include"lab4_1.h"
#include<fstream>
using namespace std;


int main(){
	srand(time(NULL));
	int seq[] = { 8,64,128,512 };
	Graph a;
	for (int i = 0; i < sizeof(seq) / sizeof(int); ++i) {
		int weight = 0;
		string temp = "0";
		temp[0] = '1' + i;
		std::ofstream ofp("../input/input" + temp + ".txt", std::ios::out | std::ios::trunc);
		if (!ofp) {
			std::cout << "Cannot open the target file1\n";
			system("pause");
			return 0;
		}

		InitGraph(a, seq[i], ofp);
		ofp.close();
		vector<dat> ans = Kruskal(a, weight);

		ofp.open("../output/result" + temp + ".txt", std::ios::out | std::ios::trunc);
		if (!ofp) {
			std::cout << "Cannot open the target file2\n";
			system("pause");
			return 0;
		}

		ofp << weight << endl;
		for (auto it = ans.begin(); it != ans.end(); ++it)
			ofp << it->first << ' ' << it->second << endl;
		ofp.close();
	}
	//ShowGraph(a);
	system("pause");
	return 0;
}
