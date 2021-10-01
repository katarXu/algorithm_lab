#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_LEN (100)

FILE* inFile(char str[20], const char *mode = "w") {
	if (strlen(str) == 0) {
		puts("input the name of the file");
		scanf_s("%s", str, 20);
	}
	if (strlen(str) < 5 || str[strlen(str) - 4] != '.') {
		sprintf_s(str, 20, "%s%s", str, (char*)".txt");
	}
	FILE *fp;
	if (fopen_s(&fp, str, mode) != 0) {
		puts("failed to open the file");
		exit(0);
	}
	return fp;
}
//预处理
void pretreat(char *devil, char **person, char **terminal, int n) {
	for (int k = 0; k < n - 1; ++k) {
		int len = strlen(person[k]);
		for (int i = 0; i < len; ++i) {
			for (int j = 1; j < n; ++j) {
				if (person[k][i] == devil[j]) {
					strncat_s(terminal[k], MAX_LEN, person[j], MAX_LEN);
				}
				else strncat_s(terminal[k], MAX_LEN, &person[k][i], 1);
			}
		}
	}
	strncat_s(terminal[n - 1], MAX_LEN, person[n - 1], MAX_LEN);
}
//处理单个入栈字符
void dispatch(char ch, char *devil, char **terminal, int n, char *ans) {
	bool flag = false;
	for (int i = 0; !flag && i < n; ++i) {
		if (ch == devil[i]) {
			strncat_s(ans, 2 * MAX_LEN, terminal[i], MAX_LEN);
			flag = true;
		}
	}
	if (!flag)
		strncat_s(ans, 200, &ch, 1);
}
//主体函数
void translate(char *word, char *devil, char **terminal, int n, char *ans) {
	int len = strlen(word);
	memset(ans, 0, sizeof(ans));
	for (int i = 0; i < len; ++i) {
		if (word[i] != '(') {
			dispatch(word[i], devil, terminal, n, ans);
		}
		else {
			++i;
			int j = i + 1;
			while (word[j] != ')') ++j;
			char ch = word[i];
			for (int k = j - 1; k > i; --k) {
				dispatch(ch, devil, terminal, n, ans);
				dispatch(word[k], devil, terminal, n, ans);
			}
			dispatch(ch, devil, terminal, n, ans);
			i = j;
		}
	}
}

int main(int argc, char *argv[]) {
	char ok = 'n';
	char str[20];
	FILE *in = stdin, *out = stdout;
	switch (argc) {
	case 1:
		puts("whether get data from file, y for yes and else for not");
		scanf_s("%c", &ok, 1);
		if (ok == 'y') {
			puts("input the name of the file to read");
			scanf_s("%s", str, 20);
			in = inFile(str, "r");
		}
		puts("whether write data in file, y for yes and else for not");
		scanf_s("%*[\n]%c", &ok, 1);
		if (ok == 'y') {
			puts("input the name of the file to write");
			scanf_s("%s", str, 20);
			out = inFile(str);
		}
		break;
	case 3:
		in = inFile(argv[1], "r");
		out = inFile(argv[2]);
		break;
	default:
		puts("the num of parameters is unexcepted");
		exit(0);
	}
	ok = 'y';
	while (ok == 'y') {
		int n;
		char word[MAX_LEN] = "";
		char ans[2 * MAX_LEN] = "";

		if (in == stdin)
			puts("input the num of orders");
		fscanf_s(in, "%d", &n);

		char *devil = (char *)calloc(n, sizeof(char));
		char **person = (char **)malloc(n * sizeof(char *));
		char **terminal = (char **)malloc(n * sizeof(char *));

		for (int i = 0; i < n; ++i) {
			person[i] = (char *)calloc(MAX_LEN, sizeof(char));
			terminal[i] = (char *)calloc(MAX_LEN, sizeof(char));
		}

		if (in == stdin)
			puts("input your orders, the devil's word first with personal word following");
		for (int i = 0; i < n; ++i)
			fscanf_s(in, "%*[\n]%c %s", &devil[i], 1, person[i], MAX_LEN);
		if (in == stdin)
			puts("input the devil's word");
		fscanf_s(in, "%s", word, MAX_LEN);

		pretreat(devil, person, terminal, n);
		translate(word, devil, terminal, n, ans);
		fprintf(out, "%s\n", ans);
		for (int i = 0; i < n; ++i) {
			free(person[i]);
			free(terminal[i]);
		}
		free(devil);
		free(person);
		free(terminal);

		ok = 'n';
		if (in == stdin) {
			puts("whether to continue, y for continue, else for not");
			fscanf_s(in, "%*[\n]%c", &ok, 1);
			puts("");
		}
		else
			if (!feof(in)) ok = 'y';
	}
	system("pause");
	return 0;
}