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
	if (sindex >= s.size() && pindex >= p.size())
		return true;
	if (sindex < s.size()  && pindex >= p.size())
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
	
	if (p.size() == 0 && s.size() == 0)return true;
	if (p.size() == 0)return false;

	return isMatch_helper(s, p, 0, 0);
}

void test19()
{
	string s = "";
	string p = ".*";
	auto res = isMatch_19(s, p);
	cout << "res = " << res << endl;
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

//21调整数组顺序使奇数位于偶数前面
vector<int> exchange(vector<int>& nums) {
	int len = nums.size();
	int left = 0;
	int right = len - 1;
	while (left < right)
	{
		while(nums[left] % 2 == 1 && left<len-1)
			left++;
		while (nums[right] % 2 == 0 && right>0)
		{
			right--;
		}
		if (left < right)
		{
			swap(nums[left], nums[right]);
		}
	}

	return nums;
}

void test21()
{
	vector<int> v{ 1,3,5 };
	auto res = exchange(v);
	cout << "ok" << endl;
}

//22链表中倒数第k个节点
ListNode* getKthFromEnd(ListNode* head, int k) {
	//k可能大于链表长度，先求链表长度再取余
	auto tmp = head;
	int count = 0;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	if (count == 0)return nullptr;
	int use_k = k % count;
	if (use_k == 0)return head;

	auto fast = head;
	auto slow = head;
	for (int i = 1; i < use_k; i++)
	{
		fast = fast->next;
	}

	while (fast->next)
	{
		fast = fast->next;
		slow = slow->next;
	}
	return slow;
}



//24反转链表
ListNode* reverseList(ListNode* head) {
	if (head == nullptr) return nullptr;
	ListNode* pre = nullptr;
	ListNode* cur = head;
	while (cur->next)
	{
		auto tmp = cur->next;
		cur->next = pre;
		pre = cur;
		cur = tmp;
	}
	cur->next = pre;
	return cur;
}

void test22()
{
	ListNode* Node1 = new ListNode(1);
	/*ListNode* Node2 = new ListNode(2);
	ListNode* Node3 = new ListNode(3);
	Node1->next = Node2;
	Node2->next = Node3;
	ListNode* Node4 = new ListNode(4);
	ListNode* Node5 = new ListNode(5);
	Node4->next = Node5;
	Node3->next = Node4;*/

	auto res = reverseList(Node1);
	cout << "ok" << endl;
}

//26树的子结构
bool isSubtree(TreeNode* A, TreeNode* B)
{
	if (B == nullptr)return true;
	if (A == nullptr)return false;
	if (A->val != B->val)
		return false;

	return isSubtree(A->left, B->left) && isSubtree(A->right, B->right);
}
bool isSubStructure(TreeNode* A, TreeNode* B) {
	if (A == nullptr && B == nullptr) return true;
	if (A == nullptr || B == nullptr)return false;
	bool res = false;
	if (A->val == B->val)
	{
		res = isSubtree(A, B);
	}
	if(!res)
	{
		res = isSubStructure(A->left, B) || isSubStructure(A->right, B);
	}
	
	return res;
}

//27二叉树的镜像
void sysTree(TreeNode* root)
{
	if (root == nullptr) return;
	auto tmp = root->left;
	root->left = root->right;
	root->right = tmp;
	sysTree(root->left);
	sysTree(root->right);
	return;
}
TreeNode* mirrorTree(TreeNode* root) {
	sysTree(root);
	return root;
}

//28对称二叉树
bool isSymmetric_helper(TreeNode* root1,TreeNode* root2)
{
	if (root1 == nullptr && root2 == nullptr) return true;
	if (root1 == nullptr || root2 == nullptr)return false;
	if (root1->val != root2->val)
		return false;
	return isSymmetric_helper(root1->left, root2->right) && isSymmetric_helper(root1->right, root2->left);
}
bool isSymmetric_offer(TreeNode* root) {
	return isSymmetric_helper(root, root);
}
void test26()
{
	/*TreeNode* root1 = new TreeNode(3);
	TreeNode* root2 = new TreeNode(4);
	TreeNode* root3 = new TreeNode(5);
	TreeNode* root4 = new TreeNode(1);
	TreeNode* root5 = new TreeNode(2);
	root1->left = root2;
	root1->right = root3;
	root2->left = root4;
	root2->right = root5;*/
	TreeNode* root1 = new TreeNode(1);
	TreeNode* root2 = new TreeNode(2);
	TreeNode* root3 = new TreeNode(2);
	root1->left = root2;
	root1->right = root3;
	TreeNode* root4 = new TreeNode(3);
	TreeNode* root5 = new TreeNode(4);
	TreeNode* root6 = new TreeNode(4);
	TreeNode* root7 = new TreeNode(3);
	root2->left = root4;
	root2->right = root5;
	root3->left = root6;
	root3->right = root7;
	/*TreeNode* root8 = new TreeNode(8);
	TreeNode* root9 = new TreeNode(9);
	root4->left = root8;
	root4->right = root9;*/
	TreeNode* node1 = new TreeNode(4);
	TreeNode* node2 = new TreeNode(8);
	TreeNode* node3 = new TreeNode(9);
	node1->left = node2;
	node1->right = node3;
	auto res = isSymmetric_offer(root1);
	cout << "res = " << "ok" << endl;
}

//29顺时针打印矩阵
void spiralOrder(vector<vector<int>>& matrix, int index,  int rows, int cols, vector<int>& res)
{
	int endx = cols - 1 - index;
	int endy = rows - 1 - index;
	//横着打一行-->
	for (int i = index; i <= endx; i++)
	{
		int number = matrix[index][i];
		res.push_back(number);
	}
	//方向向下
	if (index < endy)
	{
		for (int i = index+1; i <=endy; i++)
		{
			int number = matrix[i][endx];
			res.push_back(number);
		}
	}
	//方向向左
	if (index <endx && index<endy)
	{
		for (int i = endx-1; i >=index; i--)
		{
			int number = matrix[endy][i];
			res.push_back(number);
		}
	}
	//方向向上
	if (index < endy - 1 && index < endx)
	{
		for (int i = endy-1; i > index ; i--)
		{
			int number = matrix[i][index];
			res.push_back(number);
		}
	}
}
vector<int> spiralOrder(vector<vector<int>>& matrix) {
	vector<int> res;
	int rows = matrix.size();
	if (rows == 0) return res;
	int cols = matrix[0].size();
	int start = 0;
	
	while (rows > start * 2 && cols > start * 2)
	{
		spiralOrder(matrix, start, rows, cols, res);
		start++;
	}
	
	return res;
}
//转圈遍历
vector<int> spiralOrder_ans(vector<vector<int>>& matrix)
{
	vector<int> res;
	int rows = matrix.size();
	if (rows == 0)return res;
	int cols = matrix[0].size();
	int left = 0;
	int right = cols - 1;
	int top = 0;
	int bottom = rows - 1;
	int num = rows * cols;
	while (num >= 1)
	{
		//从左到右
		for (int i = left; i <= right && num >= 1; i++)
		{
			res.push_back(matrix[top][i]);
			num--;
		}
		top++;
		//从上到下
		for (int i = top; i <= bottom && num >= 1; i++)
		{
			res.push_back(matrix[i][right]);
			num--;
		}
		right--;
		//从右往左
		for (int i = right; i >= left && num >= 1; i--)
		{
			res.push_back(matrix[bottom][i]);
			num--;
		}
		bottom--;
		//从下往上
		for (int i = bottom; i >= top && num >= 1; i--)
		{
			res.push_back(matrix[i][left]);
			num--;
		}
		left++;
	}
	return res;
}

void test29()
{
	vector<vector<int>> v{
		{1,2,3},
		{4,5,6},
		{7,8,9},
	};

	auto res = spiralOrder_ans(v);
	cout << "res = " << endl;
}

//包含min函数的栈
class MinStack {
public:
	/** initialize your data structure here. */
	MinStack() {
		
	}

	void push(int x) {
		datastack.push(x);
		if (minstack.size() == 0)
		{
			minstack.push(x);
		}
		else
		{
			if (x <= minstack.top())
			{
				minstack.push(x);
			}
		}
			

	}

	void pop() {
		if (datastack.size() == 0)return;
		if (datastack.top() == minstack.top())
		{
			datastack.pop();
			minstack.pop();
		}
		else
		{
			datastack.pop();
		}
	}

	int top() {
		if (datastack.size() == 0)
		{
			throw "stack is empty";
			abort();
		}
			
		return datastack.top();
	}

	int min() {
		if (datastack.size() == 0 || minstack.size() == 0)
		{
			throw "stack is empty";
			abort();
		}
		return minstack.top();
	}

private:
	stack<int> datastack;
	stack<int> minstack;
};

void test30()
{
	MinStack m;
	auto tmp = m.top();
	m.push(-2);
	m.push(0);
	m.push(-3);
	auto res = m.min();
	m.pop();
	auto res2 = m.top();
	auto res3 = m.min();
}

//31栈的压入，弹出序列
bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
	int l1 = pushed.size();
	int l2 = popped.size();
	bool res = true;
	int index2 = 0;
	int index1 = 0;
	stack<int> s;
	while (index2 < l2)
	{
		while ((s.empty() || s.top() != popped[index2]) && index1 < l1)
		{
			s.push(pushed[index1]);
			index1++;
		}
		if (index1 == l1)
		{
			if (s.top() != popped[index2])
				return false;
			
		}
		
		index2++;
		s.pop();
	}
	return res;
}

void test31()
{
	vector<int> v1{ 1,2,3,4,5 };
	vector<int> v2{ 4,3,5,1,2 };
	bool res = validateStackSequences(v1, v2);
	cout << "res = " << res << endl;
}

//32 从上到下打印二叉树
vector<int> levelOrder_offer(TreeNode* root) {
	vector<int> res;
	if (root == nullptr) return res;

	deque<TreeNode*> node_deque;
	node_deque.push_back(root);

	while (!node_deque.empty())
	{
		int size = node_deque.size();
		for (int i = 0; i < size; i++)
		{
			auto node = node_deque.front();
			node_deque.pop_front();
			res.push_back(node->val);
			if (node->left)
			{
				node_deque.push_back(node->left);
			}
			if (node->right)
			{
				node_deque.push_back(node->right);
			}
		}
	}
	return res;
}

//32-2 从上到下打印二叉树 按层摆放
vector<vector<int>> levelOrder_offer_v2(TreeNode* root) {
	vector<vector<int>> res;
	if (root == nullptr) return res;

	deque<TreeNode*> node_deque;
	node_deque.push_back(root);

	while (!node_deque.empty())
	{
		int size = node_deque.size();
		vector<int> tmp;
		for (int i = 0; i < size; i++)
		{
			auto node = node_deque.front();
			node_deque.pop_front();
			tmp.push_back(node->val);
			if (node->left)
			{
				node_deque.push_back(node->left);
			}
			if (node->right)
			{
				node_deque.push_back(node->right);
			}
		}
		res.push_back(tmp);
	}
	return res;
}

//32-3 从上到下打印二叉树 按层摆放,"之"型摆放
vector<vector<int>> levelOrder_offer_v3(TreeNode* root) {
	vector<vector<int>> res;
	if (root == nullptr) return res;

	deque<TreeNode*> node_deque;
	node_deque.push_back(root);
	int index = 0;

	while (!node_deque.empty())
	{
		int size = node_deque.size();
		vector<int> tmp;
		for (int i = 0; i < size; i++)
		{
			auto node = node_deque.front();
			node_deque.pop_front();
			tmp.push_back(node->val);
			if (node->left)
			{
				node_deque.push_back(node->left);
			}
			if (node->right)
			{
				node_deque.push_back(node->right);
			}
		}
		if (index % 2 != 0)
		{
			reverse(tmp.begin(), tmp.end());
		}
		res.push_back(tmp);
		index++;
	}
	return res;
}

void test32()
{
	TreeNode* root1 = new TreeNode(1);
	TreeNode* root2 = new TreeNode(2);
	TreeNode* root3 = new TreeNode(3);
	root1->left = root2;
	root1->right = root3;
	TreeNode* root4 = new TreeNode(3);
	TreeNode* root5 = new TreeNode(4);
	TreeNode* root6 = new TreeNode(4);
	TreeNode* root7 = new TreeNode(5);
	root2->left = root4;
	root2->right = root5;
	root3->left = root6;
	root3->right = root7;

	auto res = levelOrder_offer_v3(root1);
	cout << "res = " << endl;
}

//33 二叉搜索树的后序遍历序列
bool verifyPostorder_helper(vector<int>& postorder,int start, int end) {
	if (start == end || start> end)return true;

	int index = end - 1;
	while (index >= start && postorder[index] > postorder[end])
	{
		index--;
	}
	//左子树范围为[start,index]，右子树范围为[index+1,end-1]
	//检验左子树数值是不是都比root(postorder[end])小
	for (int tmp = index; tmp >= start; tmp--)
	{
		if (postorder[tmp] >= postorder[end])
			return false;
	}
	return verifyPostorder_helper(postorder, start, index) &&
		verifyPostorder_helper(postorder, index + 1, end - 1);
}
bool verifyPostorder(vector<int>& postorder) {
	int len = postorder.size();
	if (len == 0) return false;
	return verifyPostorder_helper(postorder, 0, len-1);
}

void test33()
{
	vector<int> v{ 5,4,3,2,1 };
	bool res = verifyPostorder(v);
	cout << "res = " << endl;
}

//34二叉树和为某一值的路径
vector<vector<int>> res34;
void pathSum_offer_helper(TreeNode* root, int &sum, int target, vector<int> &path)
{
	if (root == nullptr) return;
	sum += root->val;
	path.push_back(root->val);
	//判断是否为叶子节点
	if (root->left == nullptr && root->right==nullptr)
	{
		if (sum == target)
		{
			res34.push_back(path);
		}
	}
	pathSum_offer_helper(root->left, sum, target, path);
	pathSum_offer_helper(root->right, sum, target, path);
	sum -= root->val;
	path.pop_back();
}
vector<vector<int>> pathSum_offer(TreeNode* root, int target) {
	if (root == nullptr) return res34;
	vector<int> path;
	int sum = 0;
	pathSum_offer_helper(root, sum, target, path);
	return res34;
}

void test34()
{
	TreeNode* root1 = new TreeNode(5);
	TreeNode* root2 = new TreeNode(4);
	TreeNode* root3 = new TreeNode(8);
	root1->left = root2;
	root1->right = root3;
	TreeNode* root4 = new TreeNode(11);
	TreeNode* root5 = new TreeNode(13);
	TreeNode* root6 = new TreeNode(4);
	root2->left = root4;
	root3->left = root5;
	root3->right = root6;
	TreeNode* root7 = new TreeNode(7);
	TreeNode* root8 = new TreeNode(2);
	root4->left = root7;
	root4->right = root8;
	TreeNode* root9 = new TreeNode(5);
	TreeNode* root10 = new TreeNode(1);
	root6->left = root9;
	root6->right = root10;

	auto res = pathSum_offer(root1, 22);
	cout << "res = " << endl;
}

//35复杂链表的复制
namespace offer
{
	class Node {
	public:
		int val;
		Node* next;
		Node* random;

		Node(int _val) {
			val = _val;
			next = NULL;
			random = NULL;
		}

		Node(int _val,Node* _node):val(_val),next(_node),random(nullptr){}
	};

	Node* copyNode(Node* original, unordered_map<Node*, Node*> &nodemap)
	{
		if (original == nullptr) return nullptr;
		Node* tmp = new Node(original->val);
		nodemap.insert(pair<Node*, Node*>(original, tmp));
		tmp->next = copyNode(original->next, nodemap);
		return tmp;
	}
	Node* copyRandomList(Node* head) {
		if (head == nullptr) return nullptr;
		auto tmphead = head;
		unordered_map<Node*, Node*> nodemap;
		Node* clone = copyNode(tmphead, nodemap);
		tmphead = head;
		while (tmphead)
		{
			auto newnode = nodemap[tmphead];
			auto nextRnode = tmphead->random;
			newnode->random = nodemap[nextRnode];
			tmphead = tmphead->next;
		}
		return clone;
	}

	void test35()
	{
		Node* node5 = new Node(1);
		Node* node4 = new Node(10,node5);
		Node* node3 = new Node(11,node4);
		Node* node2 = new Node(13,node3);
		Node* node1 = new Node(7,node2);
		node1->random = nullptr;
		node2->random = node1;
		node3->random = node5;
		node4->random = node3;
		node5->random = node1;

		auto res = copyRandomList(node1);
		cout << "res = " << endl;
	}
}

//36二叉搜索树与双向链表
void treeToDoublyList_helper(TreeNode* node, TreeNode** lastindex)
{
	if (node == nullptr)return;

	if (node->left)
		treeToDoublyList_helper(node->left, lastindex);
	node->left = *lastindex;
	if (*lastindex != nullptr)
	{
		(*lastindex)->right = node;
	}
	*lastindex = node;

	if (node->right)
		treeToDoublyList_helper(node->right, lastindex);
}

TreeNode* treeToDoublyList(TreeNode* root) {
	if (root == nullptr) return nullptr;
	TreeNode* plast = nullptr;
	treeToDoublyList_helper(root, &plast);
	//plast目前指向链表最后一个元素
	TreeNode* phead = plast;
	while (phead != nullptr && phead->left!= nullptr)
	{
		phead = phead->left;
	}

	//处理两个边缘节点
	phead->left = plast;
	plast->right = phead;
	return phead;

}
void test36()
{
	vector<string> v{ "4","2","5","1","3","nullptr","nullptr" };
	auto root = buildTree_construct(v);
	auto res = treeToDoublyList(root);
	cout << "ok" << endl;
}

class Codec {
public:

	// Encodes a tree to a single string.
	string serialize(TreeNode* root) {

	}

	// Decodes your encoded data to tree.
	TreeNode* deserialize(string data) {

	}
};

//38字符串的排列
vector<string> res38;
void permutation_bt(string s,int x)
{
	if (x == s.size()-1)
	{
		res38.push_back(s);
		return;
	}
	set<int> st;
	for (int i = x; i < s.size(); i++)
	{
		if (st.find(s[i]) != st.end()) continue;
		st.insert(s[i]);
		swap(s[i], s[x]);
		permutation_bt(s, x + 1);
		swap(s[i], s[x]);
	}	
}
vector<string> permutation(string s) {
	permutation_bt(s, 0);;
	return res38;
}

//39数组中出现次数超过一半的数字
int majorityElement(vector<int>& nums) {
	sort(nums.begin(), nums.end());
	int len = nums.size();
	return nums[len / 2];
}

//40 求最小k个数
vector<int> getLeastNumbers(vector<int>& arr, int k) {
	vector<int> vec(k, 0);
	if (k == 0)return vec;

	priority_queue<int> Q;
	for (int i = 0; i < k; ++i)
	{
		Q.push(arr[i]);
	}
	for (int i = k; i < (int)arr.size(); ++i)
	{
		if (Q.top() > arr[i])
		{
			Q.pop();
			Q.push(arr[i]);
		}
	}

	for (int i = 0; i < k; ++i)
	{
		vec[i] = Q.top();
		Q.pop();
	}
	return vec;
}

//42 设计数据结构找到数据流的中位数
class MedianFinder_offer
{
public:
	MedianFinder_offer(){}

	void addNum(int num)
	{
		if (maxHeap.size() == minHeap.size())
		{
			minHeap.push(num);
			int top = minHeap.top();
			minHeap.pop();
			maxHeap.push(top);
		}
		else
		{
			maxHeap.push(num);
			int top = maxHeap.top();
			maxHeap.pop();
			minHeap.push(top);
		}
	}

	double findMedian()
	{
		if (maxHeap.size() == minHeap.size())
			return (maxHeap.top() + minHeap.top()) * 1.0 / 2;
		else
		{
			return maxHeap.top() * 1.0;
		}
	}
private:
	priority_queue<int, vector<int>, less<int>> maxHeap;//最大堆
	priority_queue<int, vector<int>, greater<int>> minHeap;//最小堆

};


//44数字序列中某一位的数字
int getnum(int digit)
{
	if (digit == 1)
		return 10;
	int count = pow(10, digit - 1);
	return 9 * count;
}
int getnumbyindex(int num, int index, int firstnum)
{
	int res = num;
	for (int i = 0; i < index; i++)
	{
		res = num % firstnum;
		firstnum = firstnum / 10;
	}
	return res / firstnum;
}
int findNthDigit(int n) {
	if (n < 0)return 0;
	int digit = 1;
	int number = 0;
	int res = 0;
	while (n >= 0)
	{
		number = digit * getnum(digit);
		if (n < number)
		{
			//获取digit的第一位数
			int firstnum = 0;
			if (digit > 1)
			{
				firstnum = pow(10, digit - 1);
			}
			//求是从firstnum开始的第几个数
			int value = n / digit + firstnum;
			int index = 0;
			if (digit > 1)
			{
				index = n % digit;
			}
			else
			{
				return value;
			}
			res = getnumbyindex(value, index, firstnum);
			break;
		}
		else
		{
			n -= number;
		}
		digit++;
	}
	return res;

}

void testoffer44()
{
	auto res = findNthDigit(10);
	cout << "res = " << res << endl;
}

//45 把数组排成最小的数
void quicksort44(vector<string>& v, int left, int right)
{
	if (left >= right)return;
	string pivotValue = v[left];
	int i = left, j = right;
	while (i < j)
	{
		while (i < j && v[j] + pivotValue >= pivotValue + v[j])
			j--;
		swap(v[i], v[j]);
		while (i < j && v[i] + pivotValue <= pivotValue + v[i])
			i++;
		swap(v[i], v[j]);
	}
	quicksort44(v, left, i - 1);
	quicksort44(v, i + 1, right);
	
}
string minNumber(vector<int>& nums) {
	string res = "";
	vector<string> vstr;
	for (auto i : nums)
	{
		auto str = to_string(i);
		vstr.push_back(str);
	}
	quicksort44(vstr, 0, vstr.size() - 1);

	for (auto& tmp : vstr)
	{
		res += tmp;
	}
	return res;
}

void testoffer45()
{
	vector<int> v{ 3,30,34,5,9 };
	auto res = minNumber(v);
	cout << "res = " << res << endl;
}

//46把数字翻译为字符串
int translateNum(int num) {

	string str = to_string(num);
	int len = str.size();
	vector<int> dp(len+1, 0);
	dp[0] = 1;
	dp[1] = 1;
	for (int i = 2; i <= len; i++)
	{
		string tmp = str.substr(i-2,2);
		int num = atoi(tmp.c_str());
		if (num < 26 && num >= 10)
		{
			dp[i] = dp[i - 1] + dp[i - 2];
		}
		else
		{
			dp[i] = dp[i - 1];
		}
	}
	return dp[len];
}

void testoffer46()
{
	int n = 12258;
	int res = translateNum(n);
	cout << "res = " << res << endl;
}

//47礼物的最大价值
int maxValue(vector<vector<int>>& grid) {
	int res = 0;
	int rows = grid.size();
	int cols = grid[0].size();
	vector<vector<int>> dp(rows + 1, vector<int>(cols + 1, 0));
	for (int i = 1; i <= rows; i++)
	{
		for (int j = 1; j <= cols; j++)
		{
			dp[i][j] = max(dp[i - 1][j] + grid[i - 1][j - 1],
				dp[i][j - 1] + grid[i - 1][j - 1]);
		}
	}
	return dp[rows][cols];
} 

void testoffer47()
{
	vector<vector<int>> v{
		{1,3,1},
		{1,5,1},
		{4,2,1},
	};
	int res = maxValue(v);
	cout << "res = " << res << endl;
}

//48最长不重复子字符串
int lengthOfLongestSubstring_48(string s) {
	int len = s.size();
	unordered_map<char, int> window;
	int left = 0, right = 0;
	int res = 0;
	while (right < len)
	{
		char tmp = s[right];
		window[tmp]++;
		right++;

		while (window[tmp] > 1)
		{
			char p = s[left];
			window[p]--;
			left++;
		}
		res = max(res, right - left);
	}
	return res;
}

void testoffer48()
{
	string s = "pwwkew";
	int res = lengthOfLongestSubstring_48(s);
	cout << "res = " << res << endl;
}

//49丑数
int nthUglyNumber(int n) {
	set<int> numset;
	priority_queue <int, vector<int>, greater<int> > q;
	numset.insert(1);
	q.push(1);
	int res = 0;
	vector<int> factor{ 2,3,5 };

	for (int i = 0; i < n; i++)
	{
		res = q.top();
		q.pop();

		for (int i = 0; i < 3; i++)
		{
			int tmp = factor[i] * res;
			if (numset.count(tmp) == 0)
			{
				numset.insert(tmp);
				q.push(tmp);
			}
		}

	}
	return res;
}

void testoffer49()
{
	int res = nthUglyNumber(10);
	cout << "res = " << res << endl;
}

//50第一个只出现一次的字符
char firstUniqChar(string s) {
	int len = s.size();
	char res = ' ';
	unordered_map<char, int> cmap;
	for (int i = 0; i < len; i++)
	{
		cmap[s[i]]++;
	}
	for (int i = 0; i < len; i++)
	{
		if (cmap[s[i]] == 1)
		{
			res = s[i];
			break;
		}
	}
	return res;
}

void testoffer50()
{
	string s = "abaccdeff";
	auto res = firstUniqChar(s);
	cout << "res = " << res << endl;
}

//51数组中的逆序对
int res51 = 0;
void reversePairsMerge(vector<int>& nums, int left, int middle, int right)
{
	vector<int> tmp(right - left + 1 , 0);
	int lindex = left, rindex = middle + 1;
	int tindex = 0;
	while (lindex <= middle && rindex <= right)
	{
		if (nums[lindex] > nums[rindex])
		{
			tmp[tindex++] = nums[rindex++];
			res51 += middle - lindex + 1;

		}
		else
		{
			tmp[tindex++] = nums[lindex++];
		}
	}
	while (lindex <= middle)
	{
		tmp[tindex++] = nums[lindex++];
	}
	while (rindex <= right)
	{
		tmp[tindex++] = nums[rindex++];
	}
	tindex = 0;
	while (left <= right)
	{
		nums[left++] = tmp[tindex++];
	}
}
void reversePairsMergeSort(vector<int>& nums,int left,int right)
{
	if (left >= right)return;
	int middle = (left + right) / 2;
	reversePairsMergeSort(nums, left, middle);
	reversePairsMergeSort(nums, middle + 1, right);
	reversePairsMerge(nums, left, middle, right);

}
int reversePairs(vector<int>& nums) {
	int len = nums.size();
	reversePairsMergeSort(nums, 0, len - 1);
	return res51;
}

void testoffer51()
{
	vector<int> num{ 7,5,6,4 };
	auto res = reversePairs(num);
	cout << "res = " << res << endl;
}

//52两个链表的第一个公共节点
ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
	ListNode* res = nullptr;
	if (headA == nullptr || headB == nullptr) return nullptr;
	ListNode* ita = headA;
	ListNode* itb = headB;

	while (ita != nullptr || itb != nullptr)
	{
		if (ita == itb)
		{
			res = ita;
			break;
		}
		if (ita == nullptr)
		{
			ita = headB;
		}
		else
		{
			ita = ita->next;
		}
		if (itb == nullptr)
		{
			itb = headA;
		}
		else
		{
			itb = itb->next;
		}

		
		
	}
	return res;
}

void testoffer52()
{
	/*ListNode* no1 = new ListNode(4);
	ListNode* no2 = new ListNode(1);
	ListNode* no3 = new ListNode(8);
	ListNode* no4 = new ListNode(4);
	ListNode* no5 = new ListNode(5);
	no1->next = no2;
	no2->next = no3;
	no3->next = no4;
	no4->next = no5;
	ListNode* no6 = new ListNode(5);
	ListNode* no7 = new ListNode(0);
	ListNode* no8 = new ListNode(1);
	no6->next = no7;
	no7->next = no8;
	no8->next = no3;*/
	ListNode* no1 = new ListNode(3);
	ListNode* no2 = new ListNode(2);
	ListNode* no3 = new ListNode(3);
	no2->next = no3;
	ListNode* res = getIntersectionNode(no1, no2);
	cout << "res = " << res->val << endl;

}

//53在排序数组中查找数字1
int search_offer53(vector<int>& nums, int target) {
	int len = nums.size();
	int left = 0, right = len - 1;
	int targetIndex = -1;
	int res = 0;
	while (left <= right)
	{
		int middle = (left + right) / 2;
		if (nums[middle] == target)
		{
			targetIndex = middle;
			break;
		}
		else if (nums[middle] < target)
		{
			left = middle + 1;
		}
		else
		{
			right = middle - 1;
		}

	}
	if (targetIndex >= 0)
	{
		res = 1;
		int right = targetIndex + 1;
		while (right < len && nums[right] == target)
		{
			res++;
			right++;
		}
		int left = targetIndex - 1;
		while (left >= 0 && nums[left] == target)
		{
			res++;
			left--;
		}
	}
	return res;
}

void testoffer53()
{
	vector<int> v{1 };
	int res = search_offer53(v, 1);
	cout << "res = " << res << endl;
}

//寻找缺失的数字
int missingNumber(vector<int>& nums) {
	int len = nums.size();
	int left = 0, right = len - 1;
	int res = 0;
	while (left <= right)
	{
		int mid = (left + right) / 2;
		if (nums[mid] == mid)
		{
			if (mid == 0 || nums[mid - 1] == mid - 1)
				return mid;
			left = mid + 1;
		}
		else
		{
			right = mid - 1;
		}
	}
	return res;
}
void testoffer53_2()
{
	vector<int> v{ 1,2 };
	int res = missingNumber(v);
	cout << "res = " << res << endl;
}
//54 二叉搜索树的第k大节点
int m_k = 0;
int m_value = -1;
void dfs(TreeNode* root)
{
	if (root == nullptr) return;

	dfs(root->right);
	m_k--;
	if (m_k == 0)
	{
		m_value = root->val;
	}
	dfs(root->left);
}
int kthLargest(TreeNode* root, int k) {
	m_k = k;
	dfs(root);
	return m_value;
}

//55平衡二叉树
int isBalanced_offer55_help(TreeNode* root)
{
	if (root == nullptr)
		return 0;
	int left = isBalanced_offer55_help(root->left);

	int right = isBalanced_offer55_help(root->right);
	if (left == -1 || right == -1 || abs(left - right) > 1)
		return -1;
	else
		return 1+ max(left,right);
}
bool isBalanced_offer55(TreeNode* root)
{
	return isBalanced_offer55_help(root) >= 0 ? true : false;
}

//56数组中数字出现次数
int find1bitindex(int result)
{
	int index = 0;
	while (((result & 1)== 0)&&index < 8*sizeof(int))
	{
		result = result >> 1;
		index++;
	}
	return index;
}
bool isbit1(int num,int index)
{
	num = num >> index;
	return (num & 1);
}
vector<int> singleNumbers(vector<int>& nums) {
	vector<int> res;
	int len = nums.size();
	if (len == 0) return res;
	int spresult = 0;
	for (int i = 0; i < len; i++)
	{
		spresult = spresult ^ nums[i];
	}
	int index = find1bitindex(spresult);
	int res1 = 0, res2 = 0;
	for (int i = 0; i < len; i++)
	{
		if (isbit1(nums[i],index))
		{
			res1 = res1 ^ nums[i];
		}
		else
		{
			res2 = res2 ^ nums[i];
		}
	}
	res.push_back(res1);
	res.push_back(res2);
	return res;
}

//数组中除了一个数字只出现一次之外，其他数字都出现三次
int singleNumber_2(vector<int>& nums) {
	int res = 0, bit = 0;
	for (int i = 30; i >= 0; i--)
	{
		for (int num : nums)
		{
			bit += (num >> i) & 1;
		}
		res = res << 1;
		res += bit % 3;
		bit = 0;
	}
	return res;
}

void testoffer56()
{
	vector<int> v{ 3,4,3,3 };
	int res = singleNumber_2(v);
	cout << "res = " << res << endl;
}

//57和为s的两个数字
vector<int> twoSum_offer(vector<int>& nums, int target) {
	vector<int> res;
	int len = nums.size();
	if (len == 0)return res;
	int left = 0, right = len - 1;
	while (left < right)
	{
		if (nums[left] + nums[right] == target)
		{
			break;
		}
		else if (nums[left] + nums[right] > target)
		{
			right--;
		}
		else
		{
			left++;
		}
	}
	if (left < right)
	{
		res.push_back(nums[left]);
		res.push_back(nums[right]);
	}
	return res;
}

//57-2
vector<vector<int>> findContinuousSequence(int target) {
	vector<vector<int>> res;
	int n = target / 2 + 1;
	vector<int> num;
	for (int i = 0; i <= n; i++)
		num.push_back(i);
	vector<int> presum(n+1, 0);
	for (int i = 1; i <= n; i++)
	{
		presum[i] = presum[i - 1] + i;
	}

	for (int i = 0; i < n; i++)
	{
		int j = n;
		while (i < j)
		{
			if (presum[j] - presum[i] == target)
			{
				vector<int> tmp(num.begin() + i + 1, num.begin() + j+1);
				res.push_back(tmp);
				break;
			}
			else if (presum[j] - presum[i] > target)
			{
				j--;
			}
			else
				break;
		}
		
	}
	return res;
}


vector<vector<int>> findContinuousSequence_2(int target) {
	vector<vector<int>> res;
	int n = target / 2 + 1;
	vector<int> num;
	for (int i = 0; i <= n; i++)
		num.push_back(i);

	int left = 1, right = 1;
	int windowsum = 1;
	while (right < n)
	{
		right++;
		windowsum += right;

		while (windowsum > target)
		{
			windowsum -= left;
			left++;
		}
		if (windowsum == target)
		{
			vector<int> tmp(num.begin() + left, num.begin() + right + 1);
			res.push_back(tmp);
		}
		
	}

	return res;
}
void test57_2_offer_test()
{
	auto res = findContinuousSequence_2(15);
	cout << "ok" << endl;
}