#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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



void pac(int T, int arr[], bool is[], int n, int i, int cur, FILE *fp) {
	if (T == cur) {
		for (int i = 0; i < n; ++i)
			if (is[i]) {
				printf("%d ", arr[i]);
				fprintf(fp, "%d ", arr[i]);
			}
		puts("");
		fprintf(fp, "\n");
		return;
	}
	if (i == n)
		return;
	pac(T, arr, is, n, i + 1, cur, fp);
	if (T - cur >= arr[i]) {
		is[i] = true;
		pac(T, arr, is, n, i + 1, cur + arr[i], fp);
		is[i] = false;
	}
}
int main(int argc, char *argv[]) {
	int n = 0, T = 0;
	char str[20] = "";
	FILE *fp;
	if (argc <= 3) {
		switch (argc) {
		case 1:
			puts("input the value of the excepted T");
			scanf_s("%d", &T);
		case 2:
			T = T == 0 ? atoi(argv[1]) : T;
			puts("input the num of the items");
			scanf_s("%d", &n);
			break;
		case 3:
			T = atoi(argv[1]);
			n = atoi(argv[2]);
		}
		int *arr = (int *)malloc(n * sizeof(int));
		bool *is = (bool *)calloc(n, sizeof(n));
		puts("input the value of each item");
		for (int i = 0; i < n; ++i)
			scanf_s("%d", arr + i);
		fp = inFile(str);
		pac(T, arr, is, n, 0, 0, fp);
	}
	else {
		T = atoi(argv[1]);
		n = atoi(argv[2]);
		if (argc != 3 + atoi(argv[2]) && argc != 4 + atoi(argv[2])) {
			puts("the num of the items is wrong(1)");
			printf("your n is %d and your T is %d\n", n, T);
			exit(0);
		}
		if (argc == 4 + n) {
			if (atoi(argv[n + 3]) != 0) {
				puts("the num of the items is wrong(2)");
				printf("your n is %d and your T is %d and your files name is %d\n", n, T, atoi(argv[n + 3]));
				exit(0);
			}
			sprintf_s(str, 20, "%s", argv[n + 3]);
		}
		fp = inFile(str);
		int *arr = (int *)malloc(n * sizeof(int));
		bool *is = (bool *)calloc(n, sizeof(n));
		for (int i = 0; i < n; ++i)
			arr[i] = atoi(argv[i + 3]);
		pac(T, arr, is, n, 0, 0, fp);
	}
	fclose(fp);
	return 0;
}