#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_SIZE 100
//栈
typedef struct {
	int *base;
	int size, maxsize;
}SqStack;

FILE* inFile(char str[20]) {
	if (strlen(str) == 0) {
		puts("input the name of the file");
		scanf_s("%s", str, 20);
	}
	if (strlen(str) < 5 || str[strlen(str) - 4] != '.') {
		sprintf_s(str, 20, "%s%s", str, (char*)".txt");
	}
	FILE *fp;
	if (fopen_s(&fp, str, "a") != 0) {
		puts("failed to open the file");
		exit(0);
	}
	return fp;
}

void InitStack(SqStack *s) {
	s->base = (int *)malloc(MAX_SIZE * sizeof(int));
	if (s->base == NULL) {
		puts("failed to allocate memory");
		exit(0);
	}
	s->size = 0;
	s->maxsize = MAX_SIZE;
}

int Pop(SqStack *s) {
	if (s->size == 0)
		return -1;
	--s->size;
	return s->base[s->size];
}

bool Push(SqStack *s, int n) {
	if (s->size == s->maxsize)
		return false;
	s->base[s->size] = n;
	++s->size;
	return true;
}

void DeleteStack(SqStack *s) {
	free(s->base);
}
//主体函数
void nQueen(int n, FILE *fp) {
	SqStack s;
	InitStack(&s);
	//int row[8] = {};
	int *row = (int *)calloc(n, sizeof(int));
	bool* c = (bool *)calloc(n * 2 - 1, sizeof(bool));
	bool* l = (bool *)calloc(n * 2 - 1, sizeof(bool));
	bool* r = (bool *)calloc(n * 2 - 1, sizeof(bool));
	int j = 0, i = 0;
	while (i < n) {
		while (j < n) {
			if (c[j] || l[i + j] || r[i - j + n])
				++j;
			else {
				c[j] = l[i + j] = r[i - j + n] = true;
				Push(&s, j);
				row[i] = j;
				i += 1;
				j = 0;
				break;
			}
		}
		//回溯
		if (j == n) {
			i -= 1;
			j = Pop(&s);
			//j = row[i];
			c[j] = l[i + j] = r[i - j + n] = false;
			j += 1;
			row[i] = 0;
		}
	}
	DeleteStack(&s);
	puts("");
	for (int i = 0; i < n; ++i) {
		printf("%d ", row[i] + 1);
		fprintf(fp, "%d", row[i] + 1);
	}
	puts("");
}

int main(int argc, char *argv[]) {
	FILE *fp;
	char str[20] = "\0";
	if (argc == 1) {
		int n;
		puts("input the num of the N queen");
		scanf_s("%d", &n);
		fp = inFile(str);
		nQueen(n, fp);
	}
	else if (argc == 2) {
		fp = inFile(str);
		nQueen(atoi(argv[1]), fp);
	}
	else if (argc == 3) {
		strcpy_s(str, argv[2]);
		fp = inFile(str);
		nQueen(atoi(argv[1]), fp);
	}
	else {
		puts("the num of arguements is unexcepted");
		exit(0);
	}
	return 0;
}