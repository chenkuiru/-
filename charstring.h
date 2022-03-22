#pragma once
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

//8. 字符串转换整数 (atoi)
int myAtoi(string s) {
	int length = s.length();
	int index = 0;
	int res = 0;
	while (index < length && s[index] == ' ')
	{
		index++;
	}

	int firstIndex = index;
	int sign = 1;
	for (; index < length; index++)
	{
		if (index == firstIndex && (s[index] == '+' || s[index] == '-'))
		{
			if (s[index] == '-')
				sign = -1;
		}
		else if (isdigit(s[index]))
		{
			int number = s[index] - '0';
			if (res > INT_MAX / 10 || (res == INT_MAX / 10 && number > INT_MAX % 10))
				return INT_MAX;
			if (res < INT_MIN / 10 || (res == INT_MIN / 10 && -number < INT_MIN % 10))
				return INT_MIN;
			res = res * 10 + sign * number;

		}
		else
		{
			break;
		}
	}
	return res;
}

void test_8()
{
	string str = " -2147483647";
	auto res = myAtoi(str);
	cout << "res=" << res << endl;
}

//258. 各位相加
//给定一个非负整数 num，反复将各个位上的数字相加，直到结果为一位数。返回这个结果。
int getsum(int num)
{
	int sum = 0;
	while (num > 0)
	{
		int v = num % 10;
		sum += v;
		num = num / 10;
	}
	return sum;
}
int addDigits(int num) {
	if (num < 10 && num >= 0) return num;
	int tmp = num;
	while (tmp >= 10)
	{
		tmp = getsum(tmp);
	}
	return tmp;
}

void test_258()
{
	auto res = addDigits(888);
	cout << "res = " << res << endl;
}

//单调栈
//496. 下一个更大元素 I
vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
	unordered_map<int, int> maxnumber;
	vector<int> res;
	stack<int> s;
	for (int i = nums2.size() - 1; i >= 0; i--)
	{
		while (!s.empty() && nums2[i] >= s.top())
		{
			s.pop();
		}
		int tmp = s.empty() ? -1 : s.top();
		maxnumber.insert(pair<int, int>(nums2[i], tmp));
		s.push(nums2[i]);
	}

	for (int i = 0; i < nums1.size(); i++)
	{
		res.push_back(maxnumber[nums1[i]]);
	}
	return res;
}

//1118 一个月有多少天
vector<int> dailyTemperatures(vector<int>& T)
{
	vector<int> res;
	stack<int> s;
	for (int i = T.size() - 1; i >= 0; i--)
	{
		while (!s.empty() && T[i] >= T[s.top()])
		{
			s.pop();
		}
		int tmp = s.empty() ? -1 : s.top() - i;
		res.push_back(tmp);
		s.push(i);
	}
	return res;
}

//503 下一个更大的数2
vector<int> nextGreaterElements(vector<int>& nums) {
	int n = nums.size();
	vector<int> res(n,0);
	stack<int> s;
	for (int i = 2*n - 1; i >= 0; i--)
	{
		while (!s.empty() && nums[i%n] >= s.top())
		{
			s.pop();
		}
		int tmp = s.empty() ? -1 : s.top();
		res[i % n] = tmp;
		s.push(nums[i%n]);
	}
	return res;
}

void test_503()
{
	vector<int> v2{ 1,2,3,4,3 };
	auto vres = nextGreaterElements(v2);
	for (auto x : vres)
	{
		cout << x << endl;
	}
}

//2104 子数组范围和
void printVector(vector<int>& v, string str)
{
	cout << str<<" ";
	for (auto tmp : v)
	{
		cout << tmp <<", " ;
	}
	cout << endl;
}
long long subArrayRanges(vector<int>& nums) {
	int n = nums.size();
	vector<int> lmin(n, 0);
	vector<int> rmin(n, 0);
	vector<int> lmax(n, 0);
	vector<int> rmax(n, 0);

	stack<int> s;
	for (int i = n - 1; i >= 0; i--)
	{
		while(!s.empty() && nums[i] > nums[s.top()])
		{
			s.pop();
		}
		int tmp = s.empty() ? n : s.top();
		rmax[i] = tmp;
		s.push(i);
	}
	printVector(rmax, "rmax");

	s = stack<int>();
	for (int i = 0; i < n; i++)
	{
		while(!s.empty() && nums[i] >= nums[s.top()])
		{
			s.pop();
		}
		int tmp = s.empty() ? -1 : s.top();
		lmax[i] = tmp;
		s.push(i);
	}
	printVector(lmax, "lmax");

	s = stack<int>();
	for (int i = n - 1; i >= 0; i--)
	{
		while (!s.empty() && nums[i] < nums[s.top()])
		{
			s.pop();
		}
		int tmp = s.empty() ? n : s.top();
		rmin[i] = tmp;
		s.push(i);
	}
	

	printVector(rmin, "rmin");

	s = stack<int>();
	for (int i = 0; i < n; i++)
	{
		while (!s.empty() && nums[i] <= nums[s.top()])
		{
			s.pop();
		}
		int tmp = s.empty() ? -1 : s.top();
		lmin[i] = tmp;
		s.push(i);
	}
	printVector(lmin, "lmin");

	long long res = 0;
	for (int i = 0; i < n; i++)
	{
		res += nums[i] * 1L * (i - lmax[i]) * (rmax[i] - i);
		res -= nums[i] * 1L * (i - lmin[i]) * (rmin[i] - i);
	}
	return res;

}

long long subArrayRanges_ans(vector<int>& nums) {
	int n = nums.size();

	vector<int> lsmall(n, 0);
	vector<int> rsmall(n, 0);
	vector<int> llarge(n, 0);
	vector<int> rlarge(n, 0);

	stack<int> s;

	// 从左往右单调增栈 不能出栈的时候栈顶就是当前元素左侧最近的小于当前元素的节点
	s.push(-1);
	for (int i = 0; i < n; i++) {
		while (s.top() != -1 && nums[s.top()] > nums[i]) {
			s.pop();
		}
		lsmall[i] = s.top();
		s.push(i);
	}

	printVector(lsmall, "lmin");

	// 从右往左单调增栈 不能出栈的时候栈顶就是当前元素右侧最近的小于当前元素的节点
	s = stack<int>();
	s.push(n);
	for (int i = n - 1; i >= 0; i--) {
		while (s.top() != n && nums[s.top()] >= nums[i]) {
			s.pop();
		}
		rsmall[i] = s.top();
		s.push(i);
	}
	printVector(rsmall, "rmin");

	// 从左往右单调减栈 不能出栈的时候栈顶就是当前元素左侧最近的大于当前元素的节点
	s = stack<int>();
	s.push(-1);
	for (int i = 0; i < n; i++) {
		while (s.top() != -1 && nums[s.top()] < nums[i]) {
			s.pop();
		}
		llarge[i] = s.top();
		s.push(i);
	}
	printVector(llarge, "lmax");

	// 从右往左单调增栈 不能出栈的时候栈顶就是当前元素右侧最近的大于当前元素的节点
	s = stack<int>();
	s.push(n);
	for (int i = n - 1; i >= 0; i--) {
		while (s.top() != n && nums[s.top()] <= nums[i]) {
			s.pop();
		}
		rlarge[i] = s.top();
		s.push(i);
	}

	printVector(rlarge, "rmax");

	long long ans = 0;
	for (int i = 0; i < n; i++) {
		ans += nums[i] * 1L * (i - llarge[i]) * (rlarge[i] - i);
		ans -= nums[i] * 1L * (i - lsmall[i]) * (rsmall[i] - i);
	}

	return ans;
}


void test_2104()
{
	vector<int> v{ 1,3,3 };
	auto res = subArrayRanges(v);
	cout << "res= " << res << endl;
	auto res_an = subArrayRanges_ans(v);
	cout << "res= " << res_an << endl;
}

//798得分最高的最小轮调
int getScore(vector<int>& num)
{
	int len = num.size();
	if (len == 0)return 0;
	int res = 0;
	for (int i = 0; i < len; i++)
	{
		if (num[i] <= i)
			res++;
	}
	return res;
}
vector<int> moveVector(vector<int>& nums, int k)
{
	int len = nums.size();
	if (len == 0) return vector<int>();
	k = k % len;
	vector<int> res(len,0);
	for (int i = 0; i < len; i++)
	{
		int index = i - k < 0 ? i - k + len : i - k;
		res[index] = nums[i];
	}
	return std::move(res);
}
int bestRotation(vector<int>& nums) {
	int len = nums.size();
	if (len == 0)return 0;
	int ans_index = 0;
	int max = 0;
	for (int i = 0; i < len; i++)
	{
		auto res = moveVector(nums, i);
		int score = getScore(res);
		if (score > max)
		{
			max = score;
			ans_index = i;
		}
	}
	return ans_index;
}

void test_798()
{
	vector<int> nums{ 1,3,0,2,4 };
	auto res = bestRotation(nums);
	cout << "res = " << res << endl;
}

//393. UTF-8 编码验证
bool validUtf8(vector<int>& data) {
	int n = data.size();
	if (n == 0)return false;

	int index = 0;
	bool res = true;
	while (index < n)
	{
		if (data[index] < 192)
		{
			if (data[index] > 127)
			{
				return false;
			}
			index++;
		}
		else if (data[index]>=192 && data[index]  < 224)
		{
			if (index + 1 >= n || data[index + 1] < 128)
			{
				return false;
			}
			index = index + 2;
		}
		else if (data[index] >= 224 && data[index] < 240)
		{
			if (index + 2 >= n || data[index + 1] < 128 || data[index + 2] < 128)
			{
				return false;
			}
			index = index + 3;
		}
		else if (data[index] >= 240 && data[index] < 248)
		{
			if (index + 3 >= n || data[index + 1] < 128 || data[index + 2] < 128 || data[index + 3] < 128)
			{
				return false;
			}
			index = index + 4;
		}
		else if (data[index] >= 248)
		{
			return false;
		}

	}
	return res;
}

void test_393()
{
	vector<int> v{ 235,140,4 };
	auto res = validUtf8(v);
	cout << "res:" << (res?"true":"false") << endl;
}

//720. 词典中最长的单词
string longestWord(vector<string>& words) {
	int n = words.size();
	if (n == 0)return "";
	sort(words.begin(), words.end(), [](const string& a, const string& b) {
		if(a.size()==b.size())
			return a > b;
		else
		{
			return a.size() < b.size();
		}
		 });
	string res = "";
	unordered_set<string> tmp;
	tmp.emplace("");
	for (auto& str : words)
	{
		if (tmp.count(str.substr(0, str.size() - 1)))
		{
			tmp.emplace(str);
			res = str;
		}
	}
	
	return res;
}

void test_720()
{
	vector<string> v{ "m","mo","moc","moch","mocha","l","la","lat","latt","latte","c","ca","cat"};
	auto res = longestWord(v);
	cout << "res = " << res << endl;
}

class Bank {
public:
	Bank(vector<long long>& balance) {
		m_data = balance;
	}

	bool transfer(int account1, int account2, long long money) {
		int index1 = account1 - 1;
		int index2 = account2 - 1;
		if (index1 >= m_data.size() || index2 >= m_data.size())
			return false;
		if (m_data[index1] < money) return false;
		m_data[index1] -= money;
		m_data[index2] += money;
		return true;
	}

	bool deposit(int account, long long money) {
		int index = account - 1;
		if (index >= m_data.size()) return false;

		m_data[index] += money;
		return true;
	}

	bool withdraw(int account, long long money) {
		int index = account - 1;
		if (index >= m_data.size()) return false;

		if (m_data[index] < money) return false;

		m_data[index] -= money;
		return true;
	}
private:
	vector<long long> m_data;
};

void test_2043()
{
	vector<long long> v{10, 100, 20, 50, 30};
	Bank bank(v);

	auto res1 = bank.withdraw(3, 10);
	auto res2 = bank.transfer(5, 1, 20);
	auto res3 = bank.deposit(5, 20);
	auto res4 = bank.transfer(3, 4, 15);
	auto res5 = bank.withdraw(10, 50);
}




