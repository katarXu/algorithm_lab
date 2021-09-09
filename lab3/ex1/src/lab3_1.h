#pragma once
#include<iostream>
#include<cstdlib>
#include<fstream>
#include<Windows.h>

#define RED 1
#define BLACK 2

using std::cout;
using std::cin;
using std::endl;

struct RBT {
	RBT *left = nullptr, *right = nullptr, *p = nullptr;
	int key = 0;
	int color = BLACK;
};

struct Data {
	int position = -1, mRight = -1;
};

RBT *nil = new RBT{ nullptr ,nullptr ,nullptr ,0,BLACK };
typedef RBT *node;
typedef int Color;

void leftRotate(node&, node);
void rightRotae(node&, node);
void RBInsert(node&, node);
void RBInsertFixup(node&, node);
void RBTranslant(node&, node, node);
node TreeMinimun(node);
void RBDelete(node&, node);
void RBDeleteFixup(node&, node);

inline int rand(int);
node initRBT(int, std::istream&, std::ostream&, std::ostream&, std::ostream&, std::ostream&);
void inOrder(node, std::ostream&);
Data traversal(node, int, int);
void gotoxy(short, short, int digit = 1);

void leftRotate(node &root, node x) {
	if (x && x == nil)
		return;
	node y = x->right;
	x->right = y->left;
	if (y->left != nil)
		y->left->p = x;
	y->p = x->p;
	if (x->p == nil)
		root = y;
	else if (x == x->p->left)
		x->p->left = y;
	else
		x->p->right = y;
	y->left = x;
	x->p = y;
	/*
	system("cls");
	traversal(root, 0, 0);
	gotoxy(0, 10);
	system("pause");
	*/
}

void rightRotate(node &root, node x) {
	if (x && x == nil)
		return;
	node y = x->left;
	x->left = y->right;
	if (y->right != nil)
		y->right->p = x;
	y->p = x->p;
	if (x->p == nil)
		root = y;
	else if (x == x->p->right)
		x->p->right = y;
	else
		x->p->left = y;
	y->right = x;
	x->p = y;
	/*
	system("cls");
	traversal(root, 0, 0);
	gotoxy(0, 10);
	system("pause");
	*/
}

void RBInsert(node &root, node z) {
	node y = nil;
	node x = root;
	while (x != nil) {
		y = x;
		if (z->key < x->key)
			x = x->left;
		else
			x = x->right;
	}
	z->p = y;
	if (y == nil)
		root = z;
	else if (z->key < y->key)
		y->left = z;
	else
		y->right = z;
	z->left = nil;
	z->right = nil;
	z->color = RED;
	RBInsertFixup(root, z);
}
void RBInsertFixup(node &root, node z) {
	while (z->p->color == RED) {
		if (z->p == z->p->p->left) {
			node y = z->p->p->right;
			if (y->color == RED) {
				z->p->color = BLACK;
				y->color = BLACK;
				z->p->p->color = RED;
				z = z->p->p;
			}
			else {
				if (z == z->p->right) {
					z = z->p;
					leftRotate(root, z);
				}
				z->p->color = BLACK;
				z->p->p->color = RED;
				rightRotate(root, z->p->p);
			}
		}
		else {
			node y = z->p->p->left;
			if (y->color == RED) {
				z->p->color = BLACK;
				y->color = BLACK;
				z->p->p->color = RED;
				z = z->p->p;
			}
			else {
				if (z == z->p->left) {
					z = z->p;
					rightRotate(root, z);
				}
				z->p->color = BLACK;
				z->p->p->color = RED;
				leftRotate(root, z->p->p);
			}
		}
	}
	root->color = BLACK;
}

void RBTranslant(node &root, node u, node v) {
	if (u->p == nil)
		root = v;
	else if (u == u->p->left)
		u->p->left = v;
	else
		u->p->right = v;
	v->p = u->p;
}

node TreeMinimun(node x) {
	node y = x;
	while (y->left != nil)
		y = y->left;
	return y;
}

void RBDelete(node &root, node z) {
	node y = z;
	node x = nil;
	Color yOriginalColor = y->color;
	if (z->left == nil) {
		x = z->right;
		RBTranslant(root, z, z->right);
	}
	else if (z->right == nil) {
		x = z->left;
		RBTranslant(root, z, z->left);
	}
	else {
		y = TreeMinimun(z->right);
		yOriginalColor = y->color;
		x = y->right;
		if (y->p == z)
			x->p = y;
		else {
			RBTranslant(root, y, y->right);
			y->right = z->right;
			y->right->p = y;
		}
		RBTranslant(root, z, y);
		y->left = z->left;
		y->left->p = y;
		y->color = z->color;
	}
	if (yOriginalColor == BLACK && x != nil)
		RBDeleteFixup(root, x);
}

void RBDeleteFixup(node &root, node x) {
	while (x != root&&x->color == BLACK) {
		if (x == x->p->left) {
			node w = x->p->right;
			if (w->color == RED) {
				w->color = BLACK;
				x->p->color = RED;
				leftRotate(root, x->p);
				w = x->p->right;
			}
			if (w->left->color == BLACK && w->right->color == BLACK) {
				w->color = RED;
				x = x->p;
			}
			else if (w->right->color == BLACK) {
				w->left->color = BLACK;
				w->color = RED;
				rightRotate(root, w);
				w = x->p->right;
			}
			w->color = x->p->color;
			x->p->color = BLACK;
			w->right->color = BLACK;
			leftRotate(root, x->p);
			x = root;
		}
		else {
			node w = x->p->left;
			if (w->color == RED) {
				w->color = BLACK;
				x->p->color = RED;
				rightRotate(root, x->p);
				w = x->p->left;
			}
			if (w->left->color == BLACK && w->right->color == BLACK) {
				w->color = RED;
				x = x->p;
			}
			else if (w->left->color == BLACK) {
				w->right->color = BLACK;
				w->color = RED;
				rightRotate(root, w);
				w = x->p->left;
			}
			w->color = x->p->color;
			x->p->color = BLACK;
			w->left->color = BLACK;
			rightRotate(root, x->p);
			x = root;
		}
	}
	x->color = BLACK;
}

inline int rand(int n) {
	return rand() % n;
}

node initRBT(int n, std::istream& is, std::ostream& os0, std::ostream& os1, std::ostream& ost1, std::ostream& ost2) {
	node *arr = new node[n];
	arr[0] = new RBT;
	node root = nil;

	LARGE_INTEGER t1, t2, tc;
	QueryPerformanceFrequency(&tc);
	QueryPerformanceCounter(&t1);
	for (int i = 0; i < n; ++i) {
		arr[i] = new RBT;
		is >> arr[i]->key;
		RBInsert(root, arr[i]);
	}
	QueryPerformanceCounter(&t2);
	ost1 << (t2.QuadPart - t1.QuadPart)*1.0 / tc.QuadPart << endl;
	inOrder(root, os0);
	os0 << endl;

	QueryPerformanceCounter(&t1);
	bool *flag = new bool[n] {};
	for (int i = 0; i < n; i += 4) {
		int j = rand(n);
		while (flag[j])
			j = rand(n);
		RBDelete(root, arr[j]);
		os1 << arr[j]->key << ' ';
		flag[j] = true;
	}
	QueryPerformanceCounter(&t2);
	ost2 << (t2.QuadPart - t1.QuadPart)*1.0 / tc.QuadPart << endl;
	os1 << endl;
	inOrder(root, os1);
	os1 << endl;
	return arr[0];
}

void inOrder(node x, std::ostream& os) {
	if (x->left != nil)
		inOrder(x->left, os);
	os << x->key << ' ';
	if (x->right != nil)
		inOrder(x->right, os);
}

void gotoxy(short x, short y, int digit) {
	COORD coord = { x*digit, y };
	if (x*digit > 100) {
		gotoxy(0, 20);
		return;
	}
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

Data traversal(node x, int mLeft, int high) {
	Data xData, xLeft, xRight;
	int flag = x->left != NULL ? 1 : 0;
	if (flag)
		xLeft = traversal(x->left, mLeft, high + 1);
	else
		xLeft = { mLeft, mLeft };
	if (x->right != NULL) {
		xRight = traversal(x->right, xLeft.mRight + 1 + flag, high + 1);
	}
	else
		xRight = { xLeft.mRight + flag,xLeft.mRight + flag };
	xData.position = xLeft.mRight + flag;
	xData.mRight = xRight.mRight;
	gotoxy(xData.position, high, 5);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x->color == RED ? FOREGROUND_RED : FOREGROUND_BLUE);
	cout << x->key;
	return xData;
}