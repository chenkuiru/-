#pragma once
#include <stdio.h>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

struct BinaryTreeNode
{
	int value;
	BinaryTreeNode* left;
	BinaryTreeNode* right;
};

//打印之型二叉树
void print(BinaryTreeNode* pRoot)
{
	if (pRoot == nullptr)
		return;

	std::stack<BinaryTreeNode*> stackin, stackout;
	stackin.push(pRoot);

	int flag = 0;
	while (!stackin.empty() || !stackout.empty())
	{
		if (stackout.empty())
		{
			stack<BinaryTreeNode*> tmp;
			tmp = stackout;
			stackout = stackin;
			stackin = tmp;
			if(flag>0)
				printf("\n");
			flag++;
		}

		BinaryTreeNode* pNode = stackout.top();
		stackout.pop();
		printf("%d", pNode->value);

		if (flag % 2 == 1)
		{
			if(pNode->left)
				stackin.push(pNode->left);
			if (pNode->right)
				stackin.push(pNode->right);
		}
		else
		{
			if (pNode->right)
				stackin.push(pNode->right);
			if (pNode->left)
				stackin.push(pNode->left);
		}

	}


}

//打印之型树（参考答案)
void print_Answer(BinaryTreeNode* pRoot)
{
	if (pRoot == nullptr)
		return;

	std::stack<BinaryTreeNode*> levels[2];
	int current = 0;
	int next = 1;

	levels[current].push(pRoot);

	while (levels[0].empty() || levels[1].empty())
	{
		auto pNode = levels[current].top();
		levels[current].pop();
		printf("%d", pNode->value);

		if (current == 0)
		{
			if (pNode->left)
				levels[next].push(pNode->left);
			if (pNode->right)
				levels[next].push(pNode->right);
		}
		else
		{
			if (pNode->right)
				levels[next].push(pNode->right);
			if (pNode->left)
				levels[next].push(pNode->left);
		}

		if (levels[current].empty())
		{
			printf("\n");
			current = 1 - current;
			next = 1 - next;

		}

	}
}

//二叉树路径和为某一值
void FindPath(BinaryTreeNode* pRoot, int expectedSum)
{
	if (pRoot == nullptr)
		return;
	std::vector<int> path;
	int currentSum = 0;
	FindPath(pRoot, expectedSum, path, currentSum);

}

void FindPath(BinaryTreeNode* pRoot, int expectedSum, std::vector<int>& path, int currentSum)
{
	currentSum += pRoot->value;
	path.push_back(pRoot->value);

	bool isLeaf = pRoot->left == nullptr && pRoot->right == nullptr;
	if (currentSum == expectedSum && isLeaf)
	{
		printf("the path is found");
		for (auto iter = path.begin(); iter != path.end(); iter++)
			printf("%d\t", *iter);

		printf("\n");
	}

	//不是叶结点则遍历子节点
	if (pRoot->left)
		FindPath(pRoot->left, expectedSum, path, currentSum);
	if(pRoot->right)
		FindPath(pRoot->right, expectedSum, path, currentSum);

	//这里相当于执行完当前循环准备退出到父节点，必定不满足条件，从容器中把这个节点删除
	path.pop_back();
}