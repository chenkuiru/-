#pragma once
#include <stdio.h>
#include <iostream>
#include <stack>
#include <vector>
#include <map>
#include <queue>
#include <deque>
#include <string>
#include "parameters.h"

using namespace std;

struct BinaryTreeNode
{
	int value;
	BinaryTreeNode* left;
	BinaryTreeNode* right;
};

//struct TreeNode
//{
//	int val;
//	TreeNode* left;
//	TreeNode* right;
//	TreeNode() : val(0), left(nullptr), right(nullptr) {}
//	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
//	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
//};
//32 ���в����ӡ������
vector<vector<int>> levelOrder(BinaryTreeNode* root)
{
	vector<vector<int>> res;
	if (root == nullptr)
		return res;

	deque<BinaryTreeNode*> dequeTreeNode;
	dequeTreeNode.push_back(root);
	int currentNode = 1;
	int nextNode = 0;
	vector<int> tmp;
	while (!dequeTreeNode.empty())
	{
		BinaryTreeNode* node = dequeTreeNode.front();
		dequeTreeNode.pop_front();
		currentNode--;
		tmp.push_back(node->value);

		if (node->left)
		{
			dequeTreeNode.push_back(node->left);
			nextNode++;
		}
		if (node->right)
		{
			dequeTreeNode.push_back(node->right);
			nextNode++;
		}

		if (currentNode == 0)
		{
			currentNode = nextNode;
			nextNode = 0;
			res.push_back(tmp);
			tmp.clear();
		}
			

	}
	return res;

}

vector<vector<int>> levelOrder(TreeNode* root) 
{
	vector<vector<int>> res;
	if (root == nullptr)
		return res;

	std::deque<TreeNode*> dequeTreeNode;
	dequeTreeNode.push_back(root);
	int currentNode = 1;
	int nextNode = 0;
	vector<int> tmp;
	while (!dequeTreeNode.empty())
	{
		TreeNode* node = dequeTreeNode.front();
		dequeTreeNode.pop_front();
		currentNode--;
		tmp.push_back(node->val);

		if (node->left)
		{
			dequeTreeNode.push_back(node->left);
			nextNode++;
		}
		if (node->right)
		{
			dequeTreeNode.push_back(node->right);
			nextNode++;
		}

		if (currentNode == 0)
		{
			currentNode = nextNode;
			nextNode = 0;
			res.push_back(tmp);
			tmp.clear();
		}


	}
	return res;
}

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
//ʹ��˫�˶���ʵ��
vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
	vector<vector<int>> res;
	if (root == nullptr)
		return res;
	queue<TreeNode*> nodeQueue;
	nodeQueue.push(root);
	bool isodd = true;

	while (!nodeQueue.empty())
	{
		deque<int> dequeTmp;
		int size = nodeQueue.size();//��ֵ��������������ӽڵ�����size�����仯
		for (int i = 0; i < size; i++)
		{
			auto node = nodeQueue.front();
			nodeQueue.pop();
			if (isodd)
			{
				dequeTmp.push_back(node->val);
			}
			else
			{
				dequeTmp.push_front(node->val);
			}

			if (node->left)
				nodeQueue.push(node->left);
			if (node->right)
				nodeQueue.push(node->right);
		}
		isodd = !isodd;
		vector<int> tmp{ dequeTmp.begin(),dequeTmp.end() };
		res.push_back(tmp);
	}
	return res;

}

//������·����Ϊĳһֵ

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

void FindPath(BinaryTreeNode* pRoot, int expectedSum)
{
	if (pRoot == nullptr)
		return;
	std::vector<int> path;
	int currentSum = 0;
	FindPath(pRoot, expectedSum, path, currentSum);

}

//36������������˫������
void ConvertNode(BinaryTreeNode* pNode, BinaryTreeNode** pLastNodeInList)
{
	BinaryTreeNode* pcurrent = pNode;
	if (pcurrent->left != nullptr)
		ConvertNode(pcurrent->left, pLastNodeInList);

	pcurrent->left = *pLastNodeInList;
	if (*pLastNodeInList != nullptr)
		(*pLastNodeInList)->right = pcurrent;

	*pLastNodeInList = pcurrent;

	if (pcurrent->right != nullptr)
		ConvertNode(pcurrent->right, pLastNodeInList);
}

BinaryTreeNode* Convert(BinaryTreeNode* pRoot)
{
	BinaryTreeNode* pLastInlist = nullptr;
	ConvertNode(pRoot, &pLastInlist);
	BinaryTreeNode* pHeadInlist = pLastInlist;
	while (pHeadInlist->left != nullptr && pHeadInlist != nullptr)
		pHeadInlist = pHeadInlist->left;


	return pHeadInlist;
}



//37���л�������
//���л�
void serialize(BinaryTreeNode* pRoot, ostream& stream)
{
	if (pRoot == nullptr)
	{
		stream << "$,";
		return;
	}

	stream << pRoot->value << ",";
	serialize(pRoot->left, stream);
	serialize(pRoot->right, stream);
		
}
//�����л�
bool ReadStream(istream& stream, int* number)
{
	if (stream.eof())
		return false;

	char buffer[32];
	buffer[0] = '\0';

	char ch;
	stream >> ch;
	int i = 0;
	while (!stream.eof() && ch != ',')
	{
		buffer[i++] = ch;
		stream >> ch;
	}

	bool isNumeric = false;
	if (i > 0 && buffer[0] != '$')
	{
		*number = atoi(buffer);
		isNumeric = true;
	}

	return isNumeric;
}
void Deserialize(BinaryTreeNode** pRoot, istream& stream)
{
	int number = 0;
	if (ReadStream(stream, &number))
	{
		*pRoot = new BinaryTreeNode();
		(*pRoot)->value = number;
		(*pRoot)->left = nullptr;
		(*pRoot)->right = nullptr;


		Deserialize(&((*pRoot)->left), stream);
		Deserialize(&((*pRoot)->right), stream);

	}
}

//54 �������������K��Ľڵ�
BinaryTreeNode* searchKthNode(BinaryTreeNode* pRoot, unsigned int k)
{
	BinaryTreeNode* pNode = nullptr;
	if (pRoot->left)
		pNode = searchKthNode(pRoot->left, k);

	if (pNode == nullptr)
	{
		if (k == 1)
			return pNode;
		else
			k--;
	}


	if (pRoot->right)
		pNode = searchKthNode(pRoot->right, k);

	return pNode;
}

BinaryTreeNode* KthNode(BinaryTreeNode* pRoot, unsigned int k)
{
	if (pRoot == nullptr || k == 0)
		return nullptr;

	return searchKthNode(pRoot, k);
}


//55������������
int TreeDepth(BinaryTreeNode* pRoot)
{
	if (pRoot == nullptr)
		return 0;
	int left=0, right=0;
	if (pRoot->left)
		left = TreeDepth(pRoot->left);

	if (pRoot->right)
		right = TreeDepth(pRoot->right);

	return max(left, right)+1;
}

//55-1ƽ�������
bool IsBalanced_imp(BinaryTreeNode* pRoot, std::map<BinaryTreeNode*, int> &mapin)
{
	if (pRoot == nullptr)
		return true;

	int left,right;
	map<BinaryTreeNode*, int>::iterator iter = mapin.find(pRoot);
	if (iter != mapin.end())
		left = mapin[pRoot];
	else
	{
		left = TreeDepth(pRoot);
		mapin.insert(make_pair(pRoot, left));
	}
	iter = mapin.find(pRoot);
	if (iter != mapin.end())
		right = mapin[pRoot];
	else
	{
		right = TreeDepth(pRoot);
		mapin.insert(make_pair(pRoot, right));
	}

	int diff = abs(left - right);
	if (diff > 1)
		return false;

	return IsBalanced_imp(pRoot->left, mapin) && IsBalanced_imp(pRoot->right, mapin);

}

bool IsBalanced(BinaryTreeNode* pRoot)
{
	if (pRoot == nullptr)
		return true;
	std::map<BinaryTreeNode*, int> mapin;

	return IsBalanced_imp(pRoot, mapin);

}

//55-1ƽ�������(�ο��𰸣�

bool IsBalanced(BinaryTreeNode* pRoot, int* pDepth)
{
	if (pRoot == nullptr)
	{
		*pDepth = 0;
		return true;
	}
	int left, right;
	if (IsBalanced(pRoot->left, &left) && IsBalanced(pRoot->right, &right))
	{
		if (abs(left - right) <= 1)
		{
			*pDepth = 1 + max(left, right);
			return true;
		}
	}
	return false;
}

//�Ƿ�Ϊ������
bool isValidBST(BinaryTreeNode* root, BinaryTreeNode* min, BinaryTreeNode* max) {
	if (root == nullptr)
		return true;
	if (min != nullptr && root->value <= min->value)
		return false;
	if (max != nullptr && root->value >= max->value)
		return false;


	return (isValidBST(root->left,min,root) && isValidBST(root->right,root,max));

}

//�ж�һ�����Ƿ�����Գ�
bool isSymmetric(BinaryTreeNode* left, BinaryTreeNode* right)
{
	if (left == nullptr && right == nullptr)
		return true;
	if (left == nullptr || right == nullptr)
		return false;
	if (left->value != right->value)
		return false;

	return isSymmetric(left->left, right->right) && isSymmetric(left->right, right->left);

}

bool isSymmetric(BinaryTreeNode* root)
{
	if (root == nullptr)
		return true;

	return isSymmetric(root->left, root->right);
}

// �������鹹������������
TreeNode* insertNode(TreeNode* root, int val)
{
	if (root == nullptr) return new TreeNode(val);
	if (val > root->val)
		root->right = insertNode(root->right, val);
	if (val < root->val)
		root->left = insertNode(root->left, val);

	return root;
}

TreeNode* sortedArrayToBST(vector<int>& nums)
{
	int val = nums[nums.size() / 2];
	TreeNode* root = insertNode(nullptr, val);
	for (int i = nums.size() / 2 - 1; i >= 0; i--)
	{
		auto node = insertNode(root, nums[i]);
	}
	for (int i = nums.size() / 2 + 1; i < nums.size(); i++)
	{
		auto node = insertNode(root, nums[i]);
	}
	return root;
}



//�ο���
//TreeNode* sortedArrayToBST(vector<int>& nums) {
//	return helper(nums, 0, nums.size() - 1);
//}
//
//TreeNode* helper(vector<int>& nums, int left, int right) {
//	if (left > right) {
//		return nullptr;
//	}
//
//	// ����ѡ���м�λ����ߵ�������Ϊ���ڵ�
//	int mid = (left + right) / 2;
//
//	TreeNode* root = new TreeNode(nums[mid]);
//	root->left = helper(nums, left, mid - 1);
//	root->right = helper(nums, mid + 1, right);
//	return root;
//}
//
//���ߣ�LeetCode - Solution
//���ӣ�https ://leetcode-cn.com/problems/convert-sorted-array-to-binary-search-tree/solution/jiang-you-xu-shu-zu-zhuan-huan-wei-er-cha-sou-s-33/
//��Դ�����ۣ�LeetCode��
//����Ȩ���������С���ҵת������ϵ���߻����Ȩ������ҵת����ע��������

//94 ����һ�����ڵ㣬���������������
void inordersum(vector<int>& vtor, TreeNode* root)
{
	if (root == nullptr)
		return;
	
	inordersum(vtor, root->left);
	vtor.push_back(root->val);
	inordersum(vtor, root->right);

}

vector<int> inorderTraversal(TreeNode* root) {
	vector<int> res;
	if (root == nullptr)
		return res;

	inordersum(res, root);
	return res;

}

//95����һ������ n ���������ɲ����������� n ���ڵ�����ҽڵ�ֵ�� 1 �� n ������ͬ�Ĳ�ͬ���������� �����԰�����˳�򷵻ش𰸡�
TreeNode* genrate(int left, int right)
{
	if (left >= right)
		return nullptr;
	int mid = (left + right) / 2;
	TreeNode* root = new TreeNode(mid);
	root->left = genrate(left, mid - 1);
	root->right = genrate(mid + 1, right);
	return root;
}

void genrate(TreeNode* root,int left,int right)
{
	if (left > right)
		return ;
	
	root->left = genrate(left, root->val-1);
	root->right = genrate(root->val+1, right);
}

vector<TreeNode*> generateTrees(int n)
{
	vector<TreeNode*> res;
	if (n < 1)
		return res;
	int left = 1;
	int right = 3;
	for (int i = 1; i <= n; i++)
	{
		int current_left = i;
		int current_right = i;
		while (current_left > left && current_right < right)
		{
			TreeNode* root = new TreeNode(i);
			root->left = genrate(left, current_left -1);
			root->right = genrate(current_right +1, right);
			res.push_back(root);
			current_left--;
			current_right++;
		}
		
	}
	return res;
}

//�ο���
class Solution {
public:
	vector<TreeNode*> generateTrees(int start, int end) {
		if (start > end) {
			return { nullptr };
		}
		vector<TreeNode*> allTrees;
		// ö�ٿ��и��ڵ�
		for (int i = start; i <= end; i++) {
			// ������п��е�����������
			vector<TreeNode*> leftTrees = generateTrees(start, i - 1);

			// ������п��е�����������
			vector<TreeNode*> rightTrees = generateTrees(i + 1, end);

			// ��������������ѡ��һ������������������������ѡ��һ����������ƴ�ӵ����ڵ���
			for (auto& left : leftTrees) {
				for (auto& right : rightTrees) {
					TreeNode* currTree = new TreeNode(i);
					currTree->left = left;
					currTree->right = right;
					allTrees.emplace_back(currTree);
				}
			}
		}
		return allTrees;
	}

	vector<TreeNode*> generateTrees(int n) {
		if (!n) {
			return {};
		}
		return generateTrees(1, n);
	}
};
/*
���ߣ�LeetCode - Solution
���ӣ�https ://leetcode-cn.com/problems/unique-binary-search-trees-ii/solution/bu-tong-de-er-cha-sou-suo-shu-ii-by-leetcode-solut/
��Դ�����ۣ�LeetCode��
����Ȩ���������С���ҵת������ϵ���߻����Ȩ������ҵת����ע��������

*/

//96��ͬ������������
vector<TreeNode*> generateTrees(int start,int end)
{
	if (start > end) {
		return { nullptr };
	}
	 vector<TreeNode*> allTrees;
	// ö�ٿ��и��ڵ�
	for (int i = start; i <= end; i++) {
		// ������п��е�����������
		vector<TreeNode*> leftTrees = generateTrees(start, i - 1);

		// ������п��е�����������
		vector<TreeNode*> rightTrees = generateTrees(i + 1, end);

		// ��������������ѡ��һ������������������������ѡ��һ����������ƴ�ӵ����ڵ���
		for (auto& left : leftTrees) {
			for (auto& right : rightTrees) {
				TreeNode* currTree = new TreeNode(i);
				currTree->left = left;
				currTree->right = right;
				allTrees.emplace_back(currTree);
			}
		}
	}
	return allTrees;
}


int MygenerateTrees(int start, int end)
{
	if (start > end) {
		return { 1 };
	}
	int allTrees = 0;
	// ö�ٿ��и��ڵ�
	for (int i = start; i <= end; i++) {
		// ������п��е�����������
		int leftTrees = MygenerateTrees(start, i - 1);

		// ������п��е�����������
		int rightTrees = MygenerateTrees(i + 1, end);

		// ��������������ѡ��һ������������������������ѡ��һ����������ƴ�ӵ����ڵ���
		if (leftTrees == 0 || rightTrees == 0)
		{
			allTrees += (leftTrees + rightTrees);
		}
		else
		{
			allTrees += (leftTrees * rightTrees);
		}
		
	}
	return allTrees;
}

vector<vector<int>> mem;
int countTrees(int left, int right)
{
	if (left > right)
		return 1;

	if (mem[left][right] != 0)
		return mem[left][right];

	int res = 0;
	for (int i = left; i <= right; i++)
	{
		int leftnum = countTrees(left, i - 1);
		int rightnum = countTrees(i + 1, right);
		res += leftnum * rightnum;
	}
	mem[left][right] = res;
	return res;
}

int numTrees(int n) {
	if (!n)
	{
		return 0;
	}
	
	for (int i = 0; i < n + 1; i++)
	{
		vector<int> vec;
		for (int j = 0; j < n + 1; j++)
		{
			vec.push_back(0);
		}
		mem.push_back(vec);
	}

	return countTrees(1,n);
}

// 99�ָ�����������

void midOrder(TreeNode* root, vector<TreeNode*> &vec)
{
	if (root == nullptr)
		return;
	midOrder(root->left, vec);
	vec.push_back(root);
	midOrder(root->right, vec);
}


void recoverTree(TreeNode* root) {
	vector<TreeNode*> nodeVec;
	midOrder(root, nodeVec);
	TreeNode* x = nullptr;
	TreeNode* y = nullptr;
	for (int i = 0; i < nodeVec.size()-1; i++)
	{
		if (nodeVec[i]->val > nodeVec[i + 1]->val)
		{
			y = nodeVec[i + 1];
			if (x == nullptr)
			{
				x = nodeVec[i];
			}
			else
			{
				break;
			}
		}
			
	}

	if (x != nullptr && y != nullptr)
	{
		int tmp;
		tmp = x->val;
		x->val = y->val;
		y->val = x->val;

	}
	

}

// 99�ָ�����������
TreeNode* pre;
TreeNode* x;
TreeNode* y;
void midOrder2(TreeNode* root)
{
	if (root == nullptr)
		return;

	midOrder2(root->left);
	if (pre == nullptr)
	{
		pre = root;
	}
	else
	{
		if (pre->val > root->val)
		{
			y = root;
			if (x == nullptr)
			{
				x = pre;
			}

		}
		pre = root;
	}
	

	midOrder2(root->right);
}
void recoverTree2(TreeNode* root)
{
	pre = nullptr;
	x = nullptr;
	y = nullptr;
	midOrder2(root);

	if (x != nullptr && y != nullptr)
	{
		int tmp = x->val;
		x->val = y->val;
		y->val = tmp;
	}
}

//100 ��ͬ����
bool isSameTree(TreeNode* p, TreeNode* q) {
	if (p == nullptr && q == nullptr)
		return true;
	if (p == nullptr || q == nullptr)
		return false;
	if (p->val != q->val)
		return false;

	return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
}

//101 �Գƶ�����
bool comTwoNode(TreeNode* node1, TreeNode* node2)
{
	if (node1 == nullptr && node2 == nullptr)
		return true;
	if (node1 == nullptr || node2 == nullptr)
		return false;
	if (node1->val != node2->val)
		return false;
	return comTwoNode(node1->left, node2->right) && comTwoNode(node1->right, node2->left);
}


bool isSymmetric(TreeNode* root)
{
	if (root == nullptr)
		return true;
	return comTwoNode(root->left, root->right);
}

//104������������

int maxDepth(TreeNode* root) {
	if (root == nullptr)
		return 0;

	int leftDepth = maxDepth(root->left);
	int rightDepth = maxDepth(root->right);
	int res = (leftDepth > rightDepth) ? leftDepth + 1 : rightDepth + 1;
	return res;
}

//105��ǰ���������������ؽ�������
TreeNode* buildTreehelper(vector<int>& preorder, int prestart,int preend,
	vector<int>& inorder,int instart,int inend)
{
	if (prestart > preend || instart > inend)
		return nullptr;
	TreeNode* root = new TreeNode(preorder[prestart]);
	int rootindex = 0;
	for (int i = 0; i < inorder.size(); i++)
	{
		if (inorder[i] == preorder[prestart])
		{
			rootindex = i;
			break;
		}
	}
	int inorder_left_length = rootindex - instart;
	int inorder_right_length = inend - rootindex;

	root->left = buildTreehelper(preorder, prestart + 1, prestart + inorder_left_length,
		inorder, instart, rootindex - 1);
	root->right = buildTreehelper(preorder, preend-inorder_right_length+1,preend,
		inorder, rootindex + 1,inend);
	return root;
}


TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
	if (preorder.size() == 0 || inorder.size() == 0 || preorder.size()!= inorder.size())
		return nullptr;

	return buildTreehelper(preorder, 0, preorder.size() - 1, inorder, 0, inorder.size() - 1);
}

//106 ���ݺ����������������ع�һ����
TreeNode* backbuildTreehelper(vector<int>& inorder, int instart, int inend,
	vector<int>& postorder, int poststart, int postend)
{
	if (instart > inend || poststart > postend)
		return nullptr;
	TreeNode* root = new TreeNode(postorder[postend]);
	int rootindex = 0;
	for (int i = instart; i <= inend; i++)
	{
		if (inorder[i] == postorder[postend])
		{
			rootindex = i;
			break;
		}
	}

	int inorder_left_length = rootindex - instart;

	root->left = backbuildTreehelper(inorder, instart, rootindex - 1,
		postorder, poststart, poststart + inorder_left_length - 1);
	root->right = backbuildTreehelper(inorder, rootindex + 1, inend,
		postorder, poststart + inorder_left_length, postend - 1);
	return root;
}

TreeNode* backbuildTree(vector<int>& inorder, vector<int>& postorder) {
	
	if (postorder.size() == 0 || inorder.size() == 0 || postorder.size() != inorder.size())
		return nullptr;
	int n = inorder.size();

	return backbuildTreehelper(inorder, 0, n - 1, postorder, 0, n - 1);
}

//107. �������Ĳ������ II(�ӵײ����ϱ���)
vector<vector<int>> levelOrderBottom(TreeNode* root) {
	vector<vector<int>> res;
	stack<vector<int>> datastack;
	if (root == nullptr)
		return res;
	queue<TreeNode*> nodeQueue;
	nodeQueue.push(root);

	while (!nodeQueue.empty())
	{
		deque<int> dequeTmp;
		int size = nodeQueue.size();//��ֵ��������������ӽڵ�����size�����仯
		for (int i = 0; i < size; i++)
		{
			auto node = nodeQueue.front();
			nodeQueue.pop();
			
			dequeTmp.push_back(node->val);

			if (node->left)
				nodeQueue.push(node->left);
			if (node->right)
				nodeQueue.push(node->right);
		}

		vector<int> tmp{ dequeTmp.begin(),dequeTmp.end() };
		datastack.push(tmp);
		
	}

	while (!datastack.empty())
	{
		res.push_back(datastack.top());
		datastack.pop();
	}
	return res;
}
//struct ListNode {
//	int val;
//	ListNode* next;
//	ListNode() : val(0), next(nullptr) {}
//	ListNode(int x) : val(x), next(nullptr) {}
//	ListNode(int x, ListNode* next) : val(x), next(next) {}
//};
//109. ��������ת������������
int findLength(ListNode* head)
{
	int length = 0;
	if (head == nullptr)
		return length;
	while (head)
	{
		head = head->next;
		length++;
	}
	return length;
}
TreeNode* buildTree(ListNode* &head, int left, int right)
{
	if (left > right)
		return nullptr;
	TreeNode* root = new TreeNode();
	int mid = left + (right-left) / 2;
	root->left = buildTree(head, left, mid-1);
	root->val = head->val;
	head = head->next;
	root->right = buildTree(head, mid+1, right);
	return root;
}

TreeNode* sortedListToBST(ListNode* head) {
	if (head == nullptr)
		return nullptr;
	int length = findLength(head);
	return buildTree(head, 0, length - 1);
}

//110ƽ�������(�ο��𰸣�
bool IsBalanced(TreeNode* pRoot, int* pDepth)
{
	if (pRoot == nullptr)
	{
		*pDepth = 0;
		return true;
	}
	int left, right;
	if (IsBalanced(pRoot->left, &left) && IsBalanced(pRoot->right, &right))
	{
		if (abs(left - right) <= 1)
		{
			*pDepth = 1 + max(left, right);
			return true;
		}
	}
	return false;
}

//111. ����������С���
int minDepth(TreeNode* root, int* pDepth)
{
	if (root == nullptr)
	{
		*pDepth = 0;
		return *pDepth;
	}

	int left = minDepth(root->left, pDepth);
	int right = minDepth(root->right, pDepth);
	*pDepth = min(left, right) + 1;
	return *pDepth;
}

int minDepth(TreeNode* root) {
	if (root == nullptr)
		return 0;
	int left = minDepth(root->left);
	int right = minDepth(root->right);
	if (left == 0)
		return right + 1;
	else if (right == 0)
		return left + 1;
	else 
		return min(left, right) + 1;
}
//112·����
int countsum = 0;
bool ret = false;
void hasPathSum_help(TreeNode* root, int targetSum)
{
	if (root == nullptr)
		return ;
	countsum += root->val;
	bool isleaf = false;
	if (root->left == nullptr && root->right == nullptr)
		isleaf = true;

	if (countsum == targetSum && isleaf)
	{
		ret = true;
	}
	if(root->left)
		hasPathSum_help(root->left, targetSum);
	if(root->right)
		hasPathSum_help(root->right, targetSum);

	countsum -= root->val;
}
bool hasPathSum(TreeNode* root, int targetSum) {
	hasPathSum_help(root, targetSum);
	return ret;
}
//�ο���
bool hasPathSum2(TreeNode* root, int sum) {
	if (root == nullptr) {
		return false;
	}
	if (root->left == nullptr && root->right == nullptr) {
		return sum == root->val;
	}
	return hasPathSum2(root->left, sum - root->val) ||
		hasPathSum2(root->right, sum - root->val);
}

vector<vector<int>> g_resVector;
//113·���ʹ�ӡ��·��
void pathSum_help(TreeNode* root, vector<int>& path, int targetSum)
{
	if (root == nullptr)
		return;
	countsum += root->val;
	path.push_back(root->val);

	bool isleaf = false;
	if (root->left == nullptr && root->right == nullptr)
		isleaf = true;

	if (countsum == targetSum && isleaf)
	{
		g_resVector.push_back(path);
	}

	if (root->left)
		pathSum_help(root->left, path, targetSum);
	if (root->right)
		pathSum_help(root->right, path, targetSum);

	countsum -= root->val;
	path.pop_back();

}

vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
	vector<int> path;
	pathSum_help(root, path, targetSum);
	return g_resVector;
}

//114 ������չ��Ϊ����
void flatten(TreeNode* root) {
	if (root == nullptr)
		return;

	flatten(root->left);
	flatten(root->right);
	
	TreeNode* test = root->left;
	if (test != nullptr)
	{
		while (test->right!=nullptr)
		{
			test = test->right;
		}
		test->right = root->right;
		root->right = root->left;
		root->left = nullptr;
	}
	

}

//116���ÿ���ڵ����һ���Ҳ�ڵ�ָ��
struct Node
{
	int val;
	Node* left;
	Node* right;
	Node* next;

	Node() : val(0), left(NULL), right(NULL), next(NULL) {}

	Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

	Node(int _val, Node* _left, Node* _right, Node* _next)
		: val(_val), left(_left), right(_right), next(_next) {}
};

void connectTwoNode(Node* node1, Node* node2)
{
	if (node1 == nullptr || node2 == nullptr)
		return;

	node1->next = node2;
	connectTwoNode(node1->left, node1->right);
	connectTwoNode(node2->left, node2->right);
	connectTwoNode(node1->right, node2->left);
}
Node* connect(Node* root) {
	if (root == nullptr)
		return nullptr;
	connectTwoNode(root->left, root->right);
	return root;
}

//117 
Node* connect2(Node* root) {
	if (root == nullptr)
		return nullptr;

	queue<Node*> nodeQueue;
	nodeQueue.push(root);

	while (!nodeQueue.empty())
	{
		int size = nodeQueue.size();//��ֵ��������������ӽڵ�����size�����仯
		for (int i = 0; i < size; i++)
		{
			auto node = nodeQueue.front();
			nodeQueue.pop();

			if (nodeQueue.empty())
			{
				node->next = nullptr;
			}
			else
			{
				node->next = nodeQueue.front();
			}

			if (node->left)
				nodeQueue.push(node->left);
			if (node->right)
				nodeQueue.push(node->right);
		}

	}
}

//208. ʵ�� Trie (ǰ׺��)
class Trie {
public:
	Trie():children(26) {

	}

	void insert(string word) {
		Trie* node = this;
		for (auto ch : word)
		{
			if (node->children[ch - 'a'] == nullptr)
			{
				node->children[ch - 'a'] = new Trie();
			}
			node = node->children[ch - 'a'];
		}
		node->isend = true;
	}

	bool search(string word) {
		Trie* node = this;
		for (auto str : word)
		{
			node = node->children[str - 'a'];
			if (node == nullptr)
				return false;
		}
		return node->isend;
	}

	bool startsWith(string prefix) {
		Trie* node = this;
		for (auto str : prefix)
		{
			node = node->children[str - 'a'];
			if (node == nullptr)
				return false;
		}
		return true;
	}
private:
	bool isend = false;
	vector<Trie*> children;
};

//606���ݶ����������ַ���
void tree2str_help(TreeNode* root, string& res)
{
	if (root == nullptr)
	{
		res += "";
		return;
	}
	if (root->left && root->right)
	{
		res += to_string(root->val);
	}
	if (root->left == nullptr && root->right == nullptr)
	{
		res += to_string(root->val);
	}
	
	if (root->left)
		tree2str_help(root->left,res);
	if(root->right)
		tree2str_help(root->right, res);
	res += ")";
}
string tree2str(TreeNode* root) {
	if (root == nullptr)
		return "";
	if (root->left && root->right)
	{
		return to_string(root->val) + '(' + tree2str(root->left) + ')' + '(' +
			tree2str(root->right) + ')';
	}
	if (root->left == nullptr && root->right == nullptr)
	{
		return to_string(root->val);
	}
	if (root->left != nullptr && root->right == nullptr)
	{
		return to_string(root->val) + '(' + tree2str(root->left) + ')' ;
	}
	if (root->left == nullptr && root->right != nullptr)
	{
		return to_string(root->val) + '(' + ')' + '(' +
			tree2str(root->right) + ')';
	}

}

void test606()
{
	/*TreeNode* node3 = new TreeNode(3);
	TreeNode* node4 = new TreeNode(4);
	TreeNode* node2 = new TreeNode(2,node4,nullptr);
	TreeNode* node1 = new TreeNode(1,node2,node3);*/

	TreeNode* node3 = new TreeNode(3);
	TreeNode* node4 = new TreeNode(4);
	TreeNode* node2 = new TreeNode(2, node4, nullptr);
	TreeNode* node1 = new TreeNode(1, node2, node3);
	auto res = tree2str(node1);
	cout << "res = " << res << endl;
}