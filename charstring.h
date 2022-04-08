#pragma once
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;
//5.最长回文子串
tuple<int, int> expandAroundCenter(const string& s, int left, int right) {
	while (left >= 0 && right < s.size() && s[left] == s[right]) {
		--left;
		++right;
	}
	return { left + 1, right - 1 };
}

string longestPalindrome(string s)
{
	int start = 0, end = 0;
	for (int i = 0; i < s.size(); ++i)
	{
		int left1, right1,left2,right2;
		tie(left1,right1) = expandAroundCenter(s, i, i);
		tie(left2, right2) = expandAroundCenter(s, i, i + 1);
		if (right1 - left1 > end - start)
		{
			start = left1;
			end = right1;
		}
		if (right2 - left2 > end - start)
		{
			start = left2;
			end = right2;
		}
	}
	return s.substr(start, end - start + 1);
}
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

//12整数转罗马数字
unordered_map<int, string> dic{
	{1,"I"},
	{4,"IV"},
	{5,"V"},
	{9,"IX"},
	{10,"X"},
	{40,"XL"},
	{50,"L"},
	{90,"XC"},
	{100,"C"},
	{400,"CD"},
	{500,"D"},
	{900,"CM"},
	{1000,"M"},
};
string intToRoman(int num) {
	string res = "";
	int t = 1000;
	while (t > 0)
	{
		int tmp = num / t;
		if (tmp != 0)
		{
			if (tmp >= 5)
			{
				if (tmp == 9)
				{
					res += (dic[t * tmp]);
				}	
				else
				{
					res += dic[t * 5];
					int tmpnum = tmp % 5;
					for (int i = 0; i < tmpnum; i++)
						res += dic[t];
				}
			}
			else
			{
				if (tmp != 4)
				{
					//string str(tmp, dic[t]);
					for(int i=0;i<tmp;i++)
						res += dic[t];
				}
				else
					res += (dic[t * tmp]);
				
			}
		}


		num = num % t;
		t = t / 10;

		
	}
	return res;
}

void testoffer12()
{
	auto res = intToRoman(1994);
	cout << "res = " << res << endl;
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

//954 二倍数对数组
bool canReorderDoubled(vector<int>& arr) {
	int len = arr.size();
	if (len == 0) return false;
	unordered_map<int, int> cnt;
	for (auto x : arr)
		cnt[x]++;

	if (cnt[0] % 2 != 0)return false;
	vector<int> value;
	for (auto t : cnt)
	{
		value.push_back(t.first);
	}
	sort(value.begin(), value.end(), [](int a, int b) {return abs(a) < abs(b); });

	for (auto x : value)
	{
		if (cnt[2 * x] < cnt[x])
			return false;
		else
		{
			cnt[2 * x] -= cnt[x];
		}
	}
	return true;
}


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

//1606找到处理最多请求的服务器
vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) {
	int len = arrival.size();
	int maxtime = arrival.back()+load.back();
	vector<vector<int>> state(k, vector<int>(maxtime+1,0));
	unordered_map<int, int> index_countmap;
	for (int i = 0; i < arrival.size(); i++)
	{
		int rindex = i % k;
		if (state[rindex][arrival[i]] != 0)
		{
			int curtime = arrival[i];
			int count = 0;
			for (int i = 0; i < k; i++)
			{
				int nextindex = (rindex + 1 + i + k) % k;
				if (state[nextindex][curtime] == 0)
				{
					rindex = nextindex;
					break;
				}
				count++;
			}
			if (count == k) continue;
		}
		
		index_countmap[rindex]++;
		int starttime = arrival[i];
		int runtime = load[i];
		for (int i = 0; i < runtime; i++)
		{
			if(starttime + i< maxtime)
				state[rindex][starttime + i] = 1;
		}
	}
	//计算最大负载
	int max = 0;
	vector<int> res;
	for (auto iter = index_countmap.begin(); iter != index_countmap.end(); iter++)
	{
		if (iter->second > max)
		{
			res.clear();
			max = iter->second;
			res.push_back(iter->first);
		}
		else if (iter->second == max)
		{
			res.push_back(iter->first);
		}
		else
		{

		}
	}

	return res;
}

void test1606()
{
	int k = 3;
	vector<int> arrival{ 1 };
	vector<int> load{ 1000000000 };
	auto res = busiestServers(k, arrival, load);
	cout << "1606 ok" << endl;
}

//744寻找比目标字母大的最小字母
char nextGreatestLetter(vector<char>& letters, char target) {
	int len = letters.size();
	int left = 0, right = len - 1;
	if (letters[right] <= target)return letters[0];
	while (left <= right)
	{
		int mid = (left + right) >> 1;
		if (letters[mid] <= target)
			left = mid+1;
		else
			right = mid-1;
			
	}
	return letters[left] > target ? letters[left] : letters[0];
}

void test744()
{
	vector<char> v{ 'c','f','j','m' };
	char target = 'a';
	auto res = nextGreatestLetter(v, target);
	cout << "res = " << res << endl;
}

//307区域和检索-数组可修改
class NumArray {
public:
	NumArray(vector<int>& nums) {
		m_data = nums;
		m_tree.resize(nums.size() + 1);
		for (int i = 0; i < nums.size(); i++)
		{
			add(i + 1, nums[i]);
		}
	}

	void update(int index, int val) {
		add(index + 1, val - m_data[index]);
		m_data[index] = val;
	}

	int sumRange(int left, int right) {
		return prefixSum(right + 1) - prefixSum(left);
	}

private:
	int lowBit(int x)
	{
		return x & (-x);
	}

	void add(int index, int val)
	{
		while (index < m_tree.size())
		{
			m_tree[index] += val;
			index += lowBit(index);
		}
	}

	int prefixSum(int index)
	{
		int sum = 0;
		while (index > 0)
		{
			sum += m_tree[index];
			index -= lowBit(index);
		}
		return sum;
	}

private:
	vector<int> m_data;
	vector<int> m_tree;
};
//线段树
class NumArray2 {
public:
	NumArray2(vector<int>& nums) {
		int len = nums.size();
		n = len;
		m_data.resize(len * 4);
		build(0, 0, len - 1, nums);
	}

	void update(int index, int val) {
		change(0, val, 0, n - 1, index);
	}

	int sumRange(int left, int right) {
		return range(left, right, 0, 0, n - 1);
	}

private:
	void build(int node, int left, int right, vector<int>& num)
	{
		if (left == right)
		{
			m_data[node] = num[left];
			return;
		}
		int mid = left + (right - left) / 2;
		build(node * 2 + 1, left, mid, num);
		build(node * 2 + 2, mid + 1, right, num);
		m_data[node] = m_data[node * 2 + 1] + m_data[node * 2 + 2];
	}

	void change(int rootindex, int val, int left, int right, int index)
	{
		if (left == right)
		{
			m_data[rootindex] = val;
			return;
		}
		int mid = left + (right - left) / 2;
		if (index <= mid)
		{
			change(rootindex * 2 + 1, val, left, mid,index);
		}
		else
		{
			change(rootindex * 2 + 2, val, mid + 1, right, index);
		}
		m_data[rootindex] = m_data[rootindex * 2 + 1] + m_data[rootindex * 2 + 2];

	}

	int range(int left, int right, int rootindex, int leftlimit, int rightlimit)
	{
		if (left == leftlimit && right == rightlimit)
		{
			return m_data[rootindex];
		}
		int mid = leftlimit + (rightlimit - leftlimit) / 2;
		if (mid >= right)
		{
			return range(left, right, rootindex * 2 + 1, leftlimit, mid);
		}
		else if (mid < left)
		{
			return range(left, right, rootindex * 2 + 2, mid+1, rightlimit);
		}
		else
		{
			return range(left, mid, rootindex * 2 + 1, leftlimit, mid) + range(mid+1, right, rootindex * 2 + 2, mid + 1, rightlimit);
		}
	}

private:
	vector<int> m_data;
	int n;
};

void test307()
{
	vector<int> v{ 1,2,3,4,5 };
	NumArray2 n(v);
	int t1 = n.sumRange(0, 2);
	n.update(0, 2);
	int t2 = n.sumRange(0, 2);
}

//762 二进制表示中质数个计算置位

int numberof1(int num)
{
	int count = 0;
	while (num)
	{
		num = num & (num - 1);
		count++;
	}
	return count;
}

bool isprime(int num)
{
	if (num < 2) return false;
	int n = 2;
	while (n*n <= num)
	{
		if (num % n == 0)
			return false;
		n++;
	}
	return true;
}
int countPrimeSetBits(int left, int right) {
	int count = 0;
	unordered_map<int, bool> countmap;
	for (int i = left; i <= right; i++)
	{
		int numof1 = numberof1(i);
		if (countmap.count(numof1))
		{
			if (countmap[numof1])
				count++;
		}
		else
		{
			bool tmp = isprime(numof1);
			if (tmp)
				count++;
			countmap.insert(make_pair(numof1, tmp));
		}
	}
	return count;
}

void test762()
{
	auto res = countPrimeSetBits(6, 10);
	cout << "res = " << res << endl;
}

//旋转字符串
bool rotateString(string s, string goal) {
	int len1 = s.size();
	int len2 = goal.size();
	if (len1 != len2 || len1 == 0)return false;
	string tmp = s;
	for (int i = 0; i < len1; i++)
	{
		char c = tmp[0];
		string str = tmp.substr(1, len1 - 1) + c;
		tmp = str;
		if (tmp == goal)
		{
			return true;
		}
	}
	return false;
}

void test796()
{
	string s = "abcde";
	string goal = "abced";
	bool res = rotateString(s, goal);
	cout << "res = " << res << endl;
}

//kmp算法
int self_kmp(string s, string p)
{
	int len1 = s.size();
	int len2 = p.size();
	if (len2 == 0)return -1;
	vector<int> next(len2);
	for (int i = 1, j = 0; i < len2; i++)
	{
		while (p[i] != p[j] && j > 0)
		{
			j = next[j - 1];
		}
		if (p[i] == p[j]) j++;
		next[i] = j;
	}

	for (int i = 0, j = 0; i < len1; i++)
	{
		while (s[i] != p[j] && j > 0)
		{
			j = next[j - 1];
		}
		if (s[i] == p[j])j++;
		if (j == len2)
			return i - len2 + 1;
	}
	return -1;
}

void testkmp()
{
	string haystack = "aaaaa";
	string p = "bba";
	int index = self_kmp(haystack, p);
	cout << "res = " << index << endl;
}





