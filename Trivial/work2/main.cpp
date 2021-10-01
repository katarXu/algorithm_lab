#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define MAX_SIZE 100



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
bool next = true;
//栈
template<class T>
struct SqStack{
	T *base;
	int size, maxsize;
};
template<class T>
int ii(SqStack<T> &s) {
	s.size = 1;
	return 1;
}
//栈的函数
template<class T>
void InitStack(SqStack<T> *s) {
	s->base = (T *)malloc(MAX_SIZE * sizeof(T));
	if (s->base == NULL) {
		puts("failed to allocate memory");
		exit(0);
	}
	s->size = 0;
	s->maxsize = MAX_SIZE;
}

template<class T>
T Top(SqStack<T> *s) {
	return Empty(s) ? 0 : s->base[s->size - 1];
}

template<class T>
T Pop(SqStack<T> *s) {
	if (s->size == 0)
		return -1;
	--s->size;
	return s->base[s->size];
}

template<class T>
bool Push(SqStack<T> *s, T n) {
	if (s->size == s->maxsize)
		return false;
	s->base[s->size] = n;
	++s->size;
	return true;
}

template<class T>
bool Empty(SqStack<T> *s) {
	return s->size == 0;
}

template<class T>
void DeleteStack(SqStack<T> *s) {
	free(s->base);
}
//判断运算符以及优先级
bool isOp(char ch) {
	return ch == '*' || ch == '+' || ch == '-' || ch == '/' || ch == '(' || ch == ')' || ch == '#' || ch == '^';
}

int dispatch(char op) {
	if (op == '+' || op == '-')
		return 1;
	if (op == '*' || op == '/')
		return 2;
	if (op == '^')
		return 3;
	if (op == '(')
		return 0;
	if (op == ')')
		return 10;
	return -1;
}

char priority(char op1, char op2) {
	int op11 = dispatch(op1), op22 = dispatch(op2);
	if ((op11 == 0 && op22 == 10) || (op11 == -1 && op22 == -1)) return '=';
	if (op22 == 0) return '<';
	if (op22 == 10) return '>';
	return op11 >= op22 ? '>' : '<';
}

double Operate(double b, char oper, double a) {
	switch (oper) {
	case '+':return a + b;
	case '-':return a - b;
	case '*':return a * b;
	case '/':return a / b;
	case '^':return pow(a, b);
	}
	return 0;
}
//主体函数
double evalue(FILE *in) {
	int bra = 0;
	double a, b;
	char c, oper;
	SqStack<char> optr;
	SqStack<double> opnd;
	ii(optr);
	InitStack(&optr);
	InitStack(&opnd);
	Push(&optr, '#');
	c = fgetc(in);
	if (c == 'q') {
		next = false;
		return 0.0;
	}
	while (c != '#' || Top(&optr) != '#') {
		if (!isOp(c)) {
			//读入实数
			char str[20] = "";
			scanf_s("%[0-9.]", str + 1, 20 - 1);
			str[0] = c;
			a = atoi(str);
			int i = strchr(str, '.') - str;
			if (i > 0 && i < 20) {
				double j = 0.1;
				++i;
				while (str[i] != '\0') {
					a += (str[i] - '0') * j;
					++i;
					j *= 0.1;
				}
			}
			Push(&opnd, a);
			c = fgetc(in);
		}
		else {
			if (c == '(') ++bra;
			else if (c == ')') --bra;
			else if (c == '-'&&optr.size - bra > opnd.size)
				Push(&opnd, 0.0);
			switch (priority(Top(&optr), c)) {
			case '<':
				Push(&optr, c);
				c = fgetc(in);
				break;
			case '=':
				Pop(&optr);
				c = fgetc(in);
				break;
			case '>':
				oper = Pop(&optr);
				a = Pop(&opnd);
				b = Pop(&opnd);
				Push(&opnd, Operate(a, oper, b));
			}
		}
	}
	return Top(&opnd);
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
	system("cls");
	while (next) {
		if (in == stdin)
			puts("input your expression, # for end, and q for quit");
		fscanf_s(in, "%*[\n]");
		double ans = evalue(in);
		if (next)
			fprintf(out, "%lf\n\n", ans);
	}
	return 0;
}