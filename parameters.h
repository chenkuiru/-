#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include "math.h"
using namespace std;

struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
};

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
	
};


TreeNode* buildTree(const vector<string> &v)
{
	int len = v.size();
	if (len == 0)return nullptr;
	int index = 0;

	int count = 0;
	while (index < len)
	{
		index = index + pow(2, count);
		count++;
	}

	vector<vector<TreeNode*>> nodelist;
	index = 0;
	for (int i = 0; i < count; i++)
	{
		vector<TreeNode*> tmp;
		int count = pow(2, i);
		while (count > 0)
		{
			if (v[index] == "nullptr")
			{
				TreeNode* nodet = nullptr;
				tmp.push_back(nodet);
			}
			else
			{
				int value = atoi(v[index].c_str());
				TreeNode* nodet = new TreeNode(value);
				tmp.push_back(nodet);
			}
			
			count--;
			index++;
		}
		nodelist.push_back(tmp);

	}
	for (int i = 0 ;i < nodelist.size() - 1;  i++)
	{
		auto toplist = nodelist[i];
		auto downlist = nodelist[i + 1];
		for (int i = 0; i < toplist.size(); i++)
		{
			toplist[i]->left = downlist[i*2];
			toplist[i]->right = downlist[i*2 + 1];
		}
	}

	return nodelist[0][0];
	
}