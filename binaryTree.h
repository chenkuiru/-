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

//��ӡ֮�Ͷ�����
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

//��ӡ֮�������ο���)
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

//������·����Ϊĳһֵ
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

	//����Ҷ���������ӽڵ�
	if (pRoot->left)
		FindPath(pRoot->left, expectedSum, path, currentSum);
	if(pRoot->right)
		FindPath(pRoot->right, expectedSum, path, currentSum);

	//�����൱��ִ���굱ǰѭ��׼���˳������ڵ㣬�ض��������������������а�����ڵ�ɾ��
	path.pop_back();
}