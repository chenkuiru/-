#pragma once
#include <iostream>
#include "math.h"
#include "parameters.h"
#include <unordered_set>
#include <string>
#include <stack>
#include <list>
#include <set>
#include <algorithm>

using namespace std;

void printnode(TreeNode* root, vector<int>& value)
{
	if (root == nullptr) return;
	if (root->left)
		printnode(root->left, value);
	value.push_back(root->val);
	if (root->right)
		printnode(root->right, value);
}
vector<int> findError(TreeNode* root) {
	vector<int> res;
	if (root == nullptr) return res;
	vector<int> allnum;
	printnode(root, allnum);

	int firstindex = 0;
	int endindex = 0;
	for (int i = 0; i < allnum.size() - 1; i++)
	{
		if (allnum[i] > allnum[i + 1])
		{
			firstindex = i;
			break;
		}
	}
	for (int i = allnum.size() - 1; i > 0; i--)
	{
		if (allnum[i] < allnum[i - 1])
		{
			endindex = i;
		}
	}

	return vector<int>{allnum[firstindex], allnum[endindex]};
}

//morris����������

void morrisPre(TreeNode* root)
{
	if (root == nullptr) return;
	TreeNode* cur = root;
	TreeNode* mostRight = nullptr;
	while (cur != nullptr)
	{
		mostRight = cur->left;
		if (mostRight != nullptr)
		{
			//cur�����ӣ��ҵ�cur�����������ӽڵ�
			while (mostRight->right != nullptr && mostRight->right != cur)
			{
				mostRight = mostRight->right;
			}
			//mostRight���Һ���Ϊ�գ�������ָ��cur
			if (mostRight->right == nullptr)
			{
				mostRight->right = cur;
				cout << cur->val << " " << endl;
				cur = cur->left;
				continue;
			}
			else
			{
				//mostRight���Һ���ָ��cur������ָ��գ�cur�����ƶ�
				mostRight->right = nullptr;
			}
		}
		else
		{
			cout << cur->val << " " << endl;
		}
		cur = cur->right;
	}
}


void morrisMid(TreeNode* root)
{
	if (root == nullptr) return;
	TreeNode* cur = root;
	TreeNode* mostRight = nullptr;
	while (cur != nullptr)
	{
		mostRight = cur->left;
		if (mostRight != nullptr)
		{
			//cur�����ӣ��ҵ�cur�����������ӽڵ�
			while (mostRight->right != nullptr && mostRight->right != cur)
			{
				mostRight = mostRight->right;
			}
			//mostRight���Һ���Ϊ�գ�������ָ��cur
			if (mostRight->right == nullptr)
			{
				mostRight->right = cur;
				cur = cur->left;
				continue;
			}
			else
			{
				//mostRight���Һ���ָ��cur������ָ��գ�cur�����ƶ�
				mostRight->right = nullptr;
			}
		}

		cout << cur->val << " " << endl;

		cur = cur->right;
	}
}
void test_morrisPre()
{
	vector<string> v{ "1","2","3","4","5","6","7" };
	TreeNode* root = buildTree_construct(v);
	morrisMid(root);
}



//����һ�� 1 �� n �����к�һ��ջ������������˳����ջ
//��Ҫ�ڲ�������ջ˳�������£���������ջ�ͳ�ջ���ֲ���������ֵ������ĳ�ջ����
vector<int> solve(int* a, int aLen)
{
	vector<vector<int>> maxvalue(aLen , vector<int>(2, 0));
	//��[i,n]�е����ֵ��������
	int max = INT_MIN;
	int j = 0;
	for (int i = aLen - 1; i >= 0; i--)
	{
		if (max < a[i])
		{
			max = a[i];
			j = i;
		}
		maxvalue[i][0] = max;
		maxvalue[i][1] = j;
	}
	vector<int> res;
	stack<int> s;

	for (int i = 0; i < aLen; i++)
	{
		s.push(a[i]);
		if (i == maxvalue[i][1])
		{
			res.push_back(s.top());
			s.pop();
			while (!s.empty() && i<aLen-1 && s.top()>maxvalue[i + 1][0])
			{
				res.push_back(s.top());
				s.pop();
			}
		}
	}
	while (!s.empty())
	{
		res.push_back(s.top());
		s.pop();
	}
	return res;
}

void test_cow1()
{
	int a[] = { 2,1,5,3,4 };
	auto res = solve(a, 5);
	cout << "ok" << endl;
}
//Լɪ��
int ysf(int n, int m) {

	Node* head = new Node(-1);
	Node* pre = head;
	for (int i = 0; i < n; i++)
	{
		Node* node = new Node(i+1);
		pre->next = node;
		pre = node;
	}
	pre->next = head->next;

	auto cur = head->next;
	while (cur->next != cur)
	{
		for (int i = 1; i < m-1; i++)
		{
			cur = cur->next;
		}
		cur->next = cur->next->next;
		cur = cur->next;
	}
	return cur->val;
}

void  testcow2()
{
	auto res = ysf(5, 2);
}

//���Լ��
int gcd(int a, int b)
{
	int tmp = (a < b) ? a : b;
	if (b % a == 0)return a;
	int res = 1;
	for (int i = a - 1; i >= 1; i--)
	{
		if (b % i == 0 && a % i == 0)
		{
			res = i;
			break;
		}
	}
	return res;
}

int gcd_ans(int a, int b)
{
	//շת���

	if (b % a == 0 || a % b == 0)return a % b == 0 ? b : a;
	while (a != b)
	{
		if (a > b)
			a = a - b;
		else
			b = b - a;
	}
	
	return b;
}

void testcow3()
{
	int res = gcd_ans(5, 6);
	cout << "res = " << res << endl;

}