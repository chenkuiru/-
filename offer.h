#pragma once
#include <iostream>
#include "math.h"
#include "parameters.h"
#include <unordered_set>
#include <string>
#include <stack>
#include <list>
#include <algorithm>
#include <tuple>

using namespace std;

//001 整数除法
int divide(int a, int b) {
	if (a == INT_MIN && b == -1) return INT_MAX;
	if (b == 0) return  INT_MAX;
	int sign = (a > 0) ^ (b > 0) ? -1 : 1;

	if (a > 0)a = -a;
	if (b > 0)b = -b;

	int count = 0;
	while (a<=b)
	{
		a -= b;
		count++;
	}

	
	return sign == 1 ? count: -count;
}

int divide_ans(int a, int b)
{
	if (a == 0)return 0;
	if (a == INT_MIN && b == -1) return INT_MAX;
	int sign = (a > 0) ^ (b > 0) ? -1 : 1;
	int res = 0;
	if (a == INT_MIN)
	{
		a -= -abs(b);
		res += 1;
	}
	long dd = abs(static_cast<long>(a));
	long dr = abs(static_cast<long>(b));
	
	for (int i = 31; i >= 0; i--)
	{
		if ((dd >> i) >= dr)
		{
			if (res > INT_MAX - (1 << i)) {
				return INT_MIN;
			}
			res += 1 << i;
			dd -= dr << i;
		}
	}

	return sign == 1 ? res : -res;

}
void test1()
{
	int res = divide_ans(INT_MIN, 1);
 	cout << "res=" << res << endl;
}

//03数组中重复数字
int findRepeatNumber(vector<int>& nums) {
	unordered_set<int> numset;
	for (int i = 0; i < nums.size(); i++)
	{
		if (numset.count(nums[i]))
			return nums[i];
		else
		{
			numset.insert(nums[i]);
		}
	}
	return -1;
}

int findRepeatNumber_2(vector<int>& nums) {
	int i = 0;
	while (i < nums.size())
	{
		if (nums[i] == i)
		{
			i++;
			continue;
		}
		if (nums[nums[i]] == nums[i])
			return nums[i];
		swap(nums[i], nums[nums[i]]);
	}
	return -1;
}

void test3()
{
	vector<int> v{ 2,3,1,0,2,5,3 };
	auto res = findRepeatNumber(v);
	cout << "res=" << res << endl;
}

//04 二维数组中的查找
bool findNumberIn2DArray(vector<vector<int>>& matrix, int target) {
	int maxrow = matrix.size();
	if (maxrow == 0)return false;
	int maxcol = matrix[0].size();

	int startrow = 0;
	int startcol = maxcol - 1;


	while (startrow < maxrow && startcol >= 0)
	{
		if (target == matrix[startrow][startcol])
			return true;
		else if (target > matrix[startrow][startcol])
		{
			startrow++;
		}
		else
		{
			startcol--;
		}
	}
	return false;
}

void test4()
{
	vector<vector<int>> matrix{
		{1,4,7,11,15},
		{2,5,8,12,19},
		{3,6,9,16,22},
		{10,13,14,17,24},
		{18,21,23,26,30},
	};
	bool res = findNumberIn2DArray(matrix, 20);
	cout << "res=" << res << endl;
}

//05替换空格
string replaceSpace(string s) {
	int len = s.size();
	int count = 0;
	for (int i = 0; i < len; i++)
	{
		if (s[i] == ' ')
		{
			count++;
		}
	}
	int newlen = len + 2 * count;
	string newstr(newlen, ' ');

	int oldindex = len - 1;
	int newindex = newlen - 1;
	while (oldindex >= 0 && newindex >= 0)
	{
		if (s[oldindex] != ' ')
		{
			newstr[newindex] = s[oldindex];
			newindex--;
			oldindex--;
		}
		else
		{
			newstr[newindex--] = '0';
			newstr[newindex--] = '2';
			newstr[newindex--] = '%';
			oldindex--;
		}
	}

	return newstr;
}

void test5()
{
	string s = "we are happy.";
	auto res = replaceSpace(s);
	cout << "res = " << res;
}

//06从尾到头打印链表
vector<int> reversePrint(ListNode* head) {
	stack<int> numstack;
	vector<int> res;
	while(head)
	{
		numstack.push(head->val);
		head = head->next;
	}

	while (!numstack.empty())
	{
		int tmp = numstack.top();
		res.push_back(tmp);
		numstack.pop();
	}

	return res;
}

void test6()
{
	ListNode* node3 = new ListNode(2);
	ListNode* node2 = new ListNode(3,node3);
	ListNode* node1 = new ListNode(1,node2);

	vector<int> res = reversePrint(node1);
	
	for (auto it : res)
	{
		cout << it << endl;
	}
}


string output(vector<string>& words, int start)
{
	string  res = words[start];
	words.erase(words.begin() + start, words.begin() + start + 1);

	map<char, list<string>> dic;
	for (auto str : words)
	{
		dic[str[0]].push_back(str);
	}

	for (auto iter = dic.begin(); iter != dic.end(); iter++)
	{
		char key = iter->first;
		list<string> tmplist = iter->second;
		/*sort(tmplist.begin(), tmplist.end(), [](const string &a, const string &b) {
			if (a.size() != b.size())
			{
				return a.size() > b.size();
			}
			else
			{
				return a < b;
			}
		});*/
		tmplist.sort([](const string& a, const string& b) {
			if (a.size() != b.size())
			{
				return a.size() > b.size();
			}
			else
			{
				return a < b;
			}
		});
		dic[key] = tmplist;
	}

	auto tmp = res[res.size()-1];
	while (dic.find(tmp) != dic.end())
	{
		string value = dic[tmp].front();
		dic[tmp].pop_front();
		res += value;
		tmp = res[res.size() -1];
	}

	return res;
}

void test_huawei()
{
	vector<string> v{ "word","dd","da","dc","dword","d" };
	auto res = output(v, 0);
	cout << "res = " << res << endl;
}
//09 两个栈实现一个队列
class CQueue {
public:
	CQueue() {

	}

	void appendTail(int value) {
		stack1.push(value);
	}

	int deleteHead() {
		int res = -1;
		if (!stack2.empty())
		{
			res = stack2.top();
			stack2.pop();
			return res;
		}

		while (!stack1.empty())
		{
			int tmp = stack1.top();
			stack1.pop();
			stack2.push(tmp);
		}
		if (stack2.size() > 0)
		{
			res = stack2.top();
			stack2.pop();
		}
		
		return res;

	}

private:
	stack<int> stack1;
	stack<int> stack2;
};


//10斐波拉契数列
int fib(int n)
{
	if (n == 0) return 0;
	if (n == 1) return 1;
	long long c = 1000000007;

	long long tmp1 = 0;
	long long tmp2 = 1;
	int index = 1;
	while (index < n)
	{
		long long value = tmp1 + tmp2;
		tmp1 = tmp2;
		tmp2 = value%c;
		index++;
	}

	return tmp2;
}

//10-2青蛙跳台阶
int numWays(int n) {
	if (n == 0) return 0;
	if (n == 1) return 1;
	if (n == 2) return 2;
	long long c = 1000000007;

	long long tmp1 = 1;
	long long tmp2 = 2;
	int index = 2;
	while (index < n)
	{
		long long value = tmp1 + tmp2;
		tmp1 = tmp2;
		tmp2 = value % c;
		index++;
	}

	return tmp2;
}

//class Solution
//{
//public:
//	tuple<int, int> expandAroundChar(const string& s, int cur_index)
//	{
//		int left = cur_index;
//		int right = cur_index;
//
//		for (int i = cur_index - 2; i >= 0; i--)
//		{
//			if (!isalpha(s[i]))
//				left = i;
//			else
//				break;
//		}
//
//		for (int i = cur_index + 1; i < s.size(); i++)
//		{
//			if (!isalpha(s[i]))
//				right = i;
//			else
//				break;
//		}
//
//		return { left, right };
//	}
//
//	int mytest(string& s)
//	{
//		int res = -1;
//
//		for (int i = 0; i < s.size(); i++)
//		{
//			if (isalpha(s[i]))
//			{
//				auto [left, right] = expandAroundChar(s, i);
//
//				cout << left << ":" << right << endl;
//
//				if (left != right)
//				{
//					auto cur_len = right - left + 1;
//					res = max(cur_len, res);
//				}
//			}
//		}
//
//		return res;
//	}
//};

bool convert(char* data, int len)
{
	if (data == nullptr || len % 2 == 0 || len < 0) return false;
	auto max = data[0];
	int index = 0;
	for (int i = 0; i < len; i++)
	{
		if (data[i] > max)
		{
			max = data[i];
			index = i;
		}
	}
	if (index == len / 2) return true;
	if (index < len / 2)
	{
		for (int i = index; i < len / 2; i++)
		{
			data[i] = data[i + 1];
		}
		data[len / 2] = max;
	}
	else
	{
		for (int i = index; i > len / 2; i--)
		{
			data[i] = data[i - 1];
		}
		data[len / 2] = max;
	}
	
	return true;
}

void testmy()
{
	char data[] = { '7', '7', '3', '4', '5','1','2' };
	auto res = convert(data, 5);
	cout << "res = " << res << endl;

}

//11 旋转数组最小数字
int minArray(vector<int>& numbers) {
	int len = numbers.size();
	if (len == 0)return 0;
	int start = 0;
	int end = len - 1;
	
	while (start < end)
	{
		int mid = start + (end - start) / 2;
		if (numbers[mid] < numbers[end])
		{
			end = mid;
		}
		else if(numbers[mid]>numbers[end])
		{
			start = mid + 1;
		}
		else
		{
			end--;
		}
	}

	return numbers[start];
}

void test10()
{
	vector<int> v = { 3,4,5,1,2 };
	auto res = minArray(v);
	cout << "res = " << res << endl;
}
//12矩阵中的路径
vector<char> track;
bool backtrack(vector<vector<char>>& board, string &word,int i,int j,int k)
{
	int rows = board.size();
	int cols = board[0].size();
	if (i >= rows || i<0 || j>=cols || j < 0 || board[i][j] != word[k])
		return false;
	if (k == word.size() - 1) return true;

	board[i][j] = '\0';
	bool res = backtrack(board, word, i + 1, j, k + 1) || backtrack(board, word, i - 1, j, k + 1)
		|| backtrack(board, word, i, j + 1, k + 1) || backtrack(board, word, i, j - 1, k + 1);
	board[i][j] = word[k];
	return res;

}
bool exist(vector<vector<char>>& board, string word) {
	int rows = board.size();
	int cols = board[0].size();
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (backtrack(board, word, i, j, 0))
				return true;
		}
	}
	return false;
}

//13 机器人的运动范围
int res = 0;

bool isvalid(int i, int j, int k)
{
	int sum = 0;
	while (i > 0)
	{
		sum += i % 10;
		i = i / 10;
	}
	while (j > 0)
	{
		sum += j % 10;
		j = j / 10;
	}
	if (sum > k)
		return false;
	else
		return true;
}
int movingCount_help(int maxrow, int maxcol, int k, int i, int j, vector<vector<bool>> visited)
{
	if (i<0 || i>=maxrow || j<0 || j>=maxcol || !isvalid(i, j, k))
	{
		return 0;
	}
	else
	{
		if (visited[i][j])
			return 0;
		visited[i][j] = true;	
	}
	
	int sum = 1+ movingCount_help(maxrow, maxcol, k, i - 1, j,visited)+
		movingCount_help(maxrow, maxcol, k, i + 1, j,visited)+
		movingCount_help(maxrow, maxcol, k, i, j - 1,visited)+
		movingCount_help(maxrow, maxcol, k, i, j + 1,visited);
	//visited[i][j] = false;
	return sum;

}
int movingCount(int m, int n, int k) {
	if (m == 0 || n == 0)return 0;
	vector<vector<bool>> visited(m, vector<bool>(n, false));
	int out = movingCount_help(m, n, k, 0, 0,visited);
	return out;
}

void test13()
{
	int res = movingCount(2, 3, 1);
	cout << "res = " << res << endl;
}

//14剪绳子
int cuttingRope(int n) {
	if (n < 2)return 0;
	if (n == 2)return 1;
	if (n == 3)return 2;
	vector<int> dp(n + 1, 0);
	dp[1] = 1;
	dp[2] = 2;
	dp[3] = 3;

	int max = 0;
	for (int i = 4; i <= n; i++)
	{
		max = 0;
		for (int j = 1; j <= i / 2; j++)
		{
			int tmp = dp[j] * dp[i - j];
			if (max < tmp)
				max = tmp;

		}
		dp[i] = max;

	}
	return dp[n];
}

int integerBreak(int n) {
	if (n <= 3) {
		return n - 1;
	}
	int large = 1000000007;
	long long res = 1;
	while (n > 4)
	{
		res = (res * 3)%large;
		n -= 3;
	}
	res = (res * n) % large;
	return res;
}


void test14()
{
	auto res = integerBreak(10);
	cout << "res = " << res << endl;
}

//16数值的整数次方

double f(double x, int n)
{
	if (n == 1) return x;
	if (n == 0)return 1;
	if (n == -1)return 1 / x;
	
	if (n % 2 == 0)
	{
		auto tmp = f(x, n / 2);
		return tmp * tmp;
	}
	else
	{
		auto tmp = f(x, n / 2);
		if (n < 0)
		{
			return tmp * tmp * 1/x;
		}
		else
		{
			return tmp * tmp * x;
		}

	}
}

double myPow(double x, int n) {
	if (n == 0)return 1;

	double res = 1;
	
	res = f(x, n);
	
	return res;

}

void test16()
{
	double res = myPow(2, -3);
	cout << "res = " << res << endl;
}

//17 打印从1到最大的n位数(考虑大数)
vector<vector<int>> res17;
vector<string> outputv;
string genstr(vector<int>& v)
{
	int n = v.size();
	if (n == 0)return "";
	string out = "";
	for (auto tmp : v)
	{
		out += to_string(tmp);
	}
	return out;
}
void printNumbers_helper(int n, vector<int>& track)
{
	if (track.size() == n)
	{
		string tmp = genstr(track);
		outputv.push_back(tmp);
		return;
	}

	for (int i = 0; i < 10; i++)
	{
		track.push_back(i);
		//string tmp = genstr(track);
		//outputv.push_back(tmp);
		printNumbers_helper(n, track);
		track.pop_back();
	}
}
vector<string> printNumbers(int n) {
	vector<int> v;
	printNumbers_helper(n, v);
	return outputv;
}

void test17()
{
	auto v = printNumbers(3);
	cout << "ok" << endl;
}

//18删除链表节点
ListNode* deleteNode(ListNode* head, int val) {
	if (head == nullptr) return nullptr;

	ListNode* node = new ListNode(0, head);
	ListNode* tmp = node;
	while (node->next)
	{
		if (node->next->val == val)
		{
			node->next = node->next->next;
			break;
		}
		node = node->next;
	}
	return tmp->next;
}

void test18()
{
	ListNode* Node1 = new ListNode(1);
	ListNode* Node2 = new ListNode(2);
	ListNode* Node3 = new ListNode(3);
	Node1->next = Node2;
	Node2->next = Node3;
	ListNode* Node4 = new ListNode(4);
	Node3->next = Node4;

	auto out = deleteNode(Node1, 1);
	cout << "out = " << out->val << endl;
}

//19正则表达式匹配
bool isMatch_helper(const string &s, const string &p, int sindex, int pindex)
{
	if (sindex == s.size() - 1 && pindex == p.size() - 1)
		return true;
	if (sindex != s.size() - 1 && pindex == p.size() - 1)
		return false;

	if (p[pindex + 1] == '*')
	{
		if (p[pindex] == s[sindex] || (p[pindex] == '.' && sindex != s.size()))
		{
			return isMatch_helper(s, p, sindex + 1, pindex + 2) ||
				isMatch_helper(s, p, sindex + 1, pindex) ||
				isMatch_helper(s, p, sindex, pindex + 2);
		}
		else
		{
			return isMatch_helper(s, p, sindex, pindex + 2);
		}
	}
	
	if (p[pindex] == s[sindex] || (p[pindex] == '.'&& sindex!=s.size()))
		return isMatch_helper(s, p, sindex + 1, pindex + 1);

	return false;
}
bool isMatch_19(string s, string p)
{
	if (s.size() == 0 || p.size() == 0)return false;

	return isMatch_helper(s, p, 0, 0);
}

//20表示数值的字符串
bool isNumber(string s) {
	int len = s.size();
	bool numFlag = false, dotFlag = false, eFlag = false, spaceFlag = false;
	for (int i = 0; i < len; i++) {
		// 如果是数字，那么直接将 numFlag 变为 true 即可
		if ((s[i] >= '0' && s[i] <= '9') ) {
			numFlag = true;
			spaceFlag = true;
		}
		else if (s[i] == ' ')
		{
			spaceFlag = false;
		}
		else if (s[i] ==  '.' && !dotFlag && !eFlag) {
			// 如果是 .  那必须前面还出现过 .  且前面没出现过 e/E，因为如果前面出现过 e/E 再出现. 说明 e/E 后面跟着小数，不符合题意
			dotFlag = true;
		}
		else if ((s[i] ==  'e' || s[i] == 'E') && !eFlag && numFlag) {
			// 如果是 e 或 E，那必须前面没出现过 e/E，且前面出现过数字
			eFlag = true;
			numFlag = false; // 这一步很重要，将是否出现过数字的 Flag 置为 false，防止出现 123E 这种情况，即出现 e/E 后，后面没数字了
		}
		else if ((s[i] ==  '+' || s[i] ==  '-') && (i == 0 || (s[i - 1] == 'e' || s[i - 1] == 'E'))) {
			// 如果是 +/- 那必须是在第一位，或是在 e/E 的后面
		}
		else {
			// 上面情况都不满足，直接返回 false 即可，提前剪枝
			return false;
		}
	}
	return numFlag&& spaceFlag;
}

class Solution20 {
public:
	enum State {
		STATE_INITIAL,
		STATE_INT_SIGN,
		STATE_INTEGER,
		STATE_POINT,
		STATE_POINT_WITHOUT_INT,
		STATE_FRACTION,
		STATE_EXP,
		STATE_EXP_SIGN,
		STATE_EXP_NUMBER,
		STATE_END
	};

	enum CharType {
		CHAR_NUMBER,
		CHAR_EXP,
		CHAR_POINT,
		CHAR_SIGN,
		CHAR_SPACE,
		CHAR_ILLEGAL
	};

	CharType toCharType(char ch) {
		if (ch >= '0' && ch <= '9') {
			return CHAR_NUMBER;
		}
		else if (ch == 'e' || ch == 'E') {
			return CHAR_EXP;
		}
		else if (ch == '.') {
			return CHAR_POINT;
		}
		else if (ch == '+' || ch == '-') {
			return CHAR_SIGN;
		}
		else if (ch == ' ') {
			return CHAR_SPACE;
		}
		else {
			return CHAR_ILLEGAL;
		}
	}

	bool isNumber(string s) {
		unordered_map<State, unordered_map<CharType, State>> transfer{
			{
				STATE_INITIAL, {
					{CHAR_SPACE, STATE_INITIAL},
					{CHAR_NUMBER, STATE_INTEGER},
					{CHAR_POINT, STATE_POINT_WITHOUT_INT},
					{CHAR_SIGN, STATE_INT_SIGN}
				}
			}, {
				STATE_INT_SIGN, {
					{CHAR_NUMBER, STATE_INTEGER},
					{CHAR_POINT, STATE_POINT_WITHOUT_INT}
				}
			}, {
				STATE_INTEGER, {
					{CHAR_NUMBER, STATE_INTEGER},
					{CHAR_EXP, STATE_EXP},
					{CHAR_POINT, STATE_POINT},
					{CHAR_SPACE, STATE_END}
				}
			}, {
				STATE_POINT, {
					{CHAR_NUMBER, STATE_FRACTION},
					{CHAR_EXP, STATE_EXP},
					{CHAR_SPACE, STATE_END}
				}
			}, {
				STATE_POINT_WITHOUT_INT, {
					{CHAR_NUMBER, STATE_FRACTION}
				}
			}, {
				STATE_FRACTION,
				{
					{CHAR_NUMBER, STATE_FRACTION},
					{CHAR_EXP, STATE_EXP},
					{CHAR_SPACE, STATE_END}
				}
			}, {
				STATE_EXP,
				{
					{CHAR_NUMBER, STATE_EXP_NUMBER},
					{CHAR_SIGN, STATE_EXP_SIGN}
				}
			}, {
				STATE_EXP_SIGN, {
					{CHAR_NUMBER, STATE_EXP_NUMBER}
				}
			}, {
				STATE_EXP_NUMBER, {
					{CHAR_NUMBER, STATE_EXP_NUMBER},
					{CHAR_SPACE, STATE_END}
				}
			}, {
				STATE_END, {
					{CHAR_SPACE, STATE_END}
				}
			}
		};

		int len = s.length();
		State st = STATE_INITIAL;

		for (int i = 0; i < len; i++) {
			CharType typ = toCharType(s[i]);
			if (transfer[st].find(typ) == transfer[st].end()) {
				return false;
			}
			else {
				st = transfer[st][typ];
			}
		}
		return st == STATE_INTEGER || st == STATE_POINT || st == STATE_FRACTION || st == STATE_EXP_NUMBER || st == STATE_END;
	}
};


bool scanUnsignedInteger(const string& str, int &index)
{
	int before = index;
	while (index < str.size() && str[index] >= '0' && str[index] <= '9')
		index++;

	return index > before;
}


bool scanInteger(const string& str, int &index)
{
	if (str[index] == '+' || str[index] == '-')
		index++;
	return scanUnsignedInteger(str, index);
}

bool isNumber2(string s) {
	int len = s.size();
	if (len == 0) return false;
	if (len > 1)
	{
		s.erase(0, s.find_first_not_of(" "));
		s.erase(s.find_last_not_of(" ") + 1);
	}
	int index = 0;
	bool numeric = scanInteger(s, index);

	if (s[index] == '.')
	{
		index++;
		numeric = scanUnsignedInteger(s, index) || numeric;
	}
	if (s[index] == 'e' || s[index] == 'E')
	{
		++index;
		numeric = numeric && scanInteger(s, index);
	}

	return numeric && index == s.size();
}

void test20()
{
	string str = "3.";
	Solution20 s;
	auto res = s.isNumber(str);
	auto res2 = isNumber2(str);
}
