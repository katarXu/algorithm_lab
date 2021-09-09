#pragma once
#include<vector>
#include<iostream>
#include<string>

using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode *next) : val(x), next(next) {}
};

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
	void show() {
		if (this != nullptr) {
			std::cout << val << ',';
			left->show();
			right->show();
		}
		else
			std::cout << "null,";
	}
};

class Node {
public:
	int val;
	Node* next;

	Node() {}

	Node(int _val) {
		val = _val;
		next = NULL;
	}
	Node(int _val, Node* _next) {
		val = _val;
		next = _next;
	}
	Node(std::vector<int> &arr, int mode = 1) {
		if (arr.size() != 0) {
			this->val = arr[0];
			Node *pre = this;
			for (int i = 1; i < arr.size(); ++i) {
				pre->next = new Node(arr[i]);
				pre = pre->next;
			}
			if (mode)
				pre->next = this;
		}
	}
	void show() {
		Node *cur = this;
		do {
			std::cout << cur->val << ' ';
			cur = cur->next;
		} while (cur != this);
	}
};

// Encodes a tree to a single string.
string serialize(TreeNode* root) {
	if (!root) return "null";
	return to_string(root->val) + "," + serialize(root->left) + "," + serialize(root->right);
}

string serialize2(TreeNode *root) {
	if (!root) return "null";
	string res = "";
	queue<TreeNode*> q;
	q.emplace(root);
	int cnt = 1;
	while (!q.empty() && cnt > 0) {
		int n = q.size();
		for (int i = 0; i < n && cnt > 0; ++i) {
			TreeNode *tmp = q.front();
			if (tmp) {
				res += to_string(tmp->val) + ",";
				if (tmp->left) cnt++;
				q.emplace(tmp->left);
				if (tmp->right) cnt++;
				q.emplace(tmp->right);
				cnt--;
			}
			else
				res += "null,";
			q.pop();
		}
	}
	res.pop_back();
	return res;
}
TreeNode *dfs(vector<string> &arr, int &i) {
	if (arr[i] == "null") return nullptr;
	TreeNode *root = new TreeNode(stoi(arr[i]));
	root->left = dfs(arr, ++i);
	root->right = dfs(arr, ++i);
	return root;
}

// Decodes your encoded data to tree.
TreeNode* deserialize(string data) {
	vector<string> arr{ "" };
	for (char &ch : data) {
		if (ch == ',')
			arr.emplace_back("");
		else
			arr.back().push_back(ch);
	}
	int i = 0;
	return dfs(arr, i);
}