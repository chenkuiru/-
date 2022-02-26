#pragma once
//动态规划
#include <iostream>
#include <vector>

using namespace std;

//53最大连续子数组和
int maxSubArray(vector<int>& nums) {
	int length = nums.size();
	if (length == 0) return 0;
	vector<int> dp(length, 0);
	int dp_0 = nums[0];
	int dp_1 = 0;
	int res = nums[0];
	for (int i = 1; i < length; i++)
	{
		dp_1 = max(nums[i], nums[i] + dp_0);
		dp_0 = dp_1;
		res = max(res, dp_1);
	}
	return res;
}


//300最长上升子序列的长度
int lengthOfLIS(vector<int>& nums) {
	vector<int> dp(nums.size() ,1);
	for (int i = 0; i < nums.size(); ++i)
	{
		for (int j = 0; j < i; ++j)
		{
			if(nums[i]>nums[j])
				dp[i] = max(dp[i], dp[j]+1);
		}
	}
	return *max_element(dp.begin(), dp.end());
}

void test_300()
{
	vector<int> v{ -3,4,-1,2,-6,1,4};
	auto res = maxSubArray(v);
	cout << res << endl;
}


//524. 通过删除字母匹配到字典里最长单词
string findLongestWord_DP(string s, vector<string>& dic)
{
	sort(dic.rbegin(), dic.rend(), [](auto&& a, auto&& b) {return a.size() < b.size() || a.size() == b.size() && a > b; });
	vector<vector<int>> next(s.size() + 1, vector<int>(26, -1));

	for (int i = s.size() - 1; i >= 0; --i)
	{
		for (int j = 0; j < 26; ++j)
		{
			next[i][j] = (s[i] == (j + 'a')) ? i : next[i + 1][j];
		}
	}

	string ans = "";
	for (const auto& e : dic)
	{
		int state = 0;
		for (char c : e)
		{
			state = next[state][c - 'a'];
			if (state == -1) break;
		}
		if (state == -1) continue;
		if (e.length() > ans.length() || e.length() == ans.length() && e < ans)
		{
			ans = e;
		}
	}
	return ans;
}

//583. 两个字符串的删除操作
//给定两个单词 word1 和 word2 ，返回使得 word1 和  word2 相同所需的最小步数。
//每步 可以删除任意一个字符串中的一个字符。
//int minDistance(string word1, string word2) {
//
//}

//1143. 最长公共子序列
int longestCommonSubsequence(string text1, string text2) {
	int len1 = text1.length();
	int len2 = text2.length();
	if (len1 == 0 || len2 == 0) return 0;
	vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1, 0));

	for (int i = 1; i <= len1; ++i)
	{
		for (int j = 1; j <= len2; ++j)
		{
			if (text1[i-1] == text2[j-1])
			{
				dp[i][j] = dp[i - 1][j - 1] + 1;
			}
			else
			{
				dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
			}
		}
	}
	return dp[len1][len2];
}



//712. 两个字符串的最小ASCII删除和
//给定两个字符串s1 和 s2，返回 使两个字符串相等所需删除字符的 ASCII 值的最小和 。
int minimumDeleteSum(string s1, string s2) {
	int len1 = s1.length();
	int len2 = s2.length();
	vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1, 0));
	int sum = 0;
	for (int i = 1; i <= len1; i++)
	{
		sum += s1[i - 1] - 'a' + 97;
		dp[i][0] = sum;
	}
	sum = 0;
	for (int j = 1; j <= len2; j++)
	{
		sum += s2[j - 1] - 'a' + 97;
		dp[0][j] = sum;
	}

	for (int i = 1; i <= len1; i++)
	{
		for (int j = 1; j <= len2; j++)
		{
			if (s1[i - 1] == s2[j - 1])
			{
				dp[i][j] = dp[i - 1][j - 1];
			}
			else
			{
				dp[i][j] = min(dp[i][j - 1] + s2[j - 1] - 'a' + 97,
					dp[i - 1][j] + s1[i - 1] - 'a' + 97);
			}
		}
	}
	return dp[len1][len2];
}

void test_1143()
{
	string str1 = "delete";
	string str2 = "leet";
	int res = minimumDeleteSum(str1, str2);
	cout << res << endl;
}

//516最长回文子序列(单字符串使用二维dp数组）也可以将字符串反转然后求最长公共子序列
int longestPalindromeSubseq(string s) {
	int n = s.size();
	vector<vector<int>> dp(n, vector<int>(n, 0));
	for (int i = 0; i < n; i++)
	{
		dp[i][i] = 1;
	}
	//dp[i][j]代表字符串s[i...j]中最长回文子序列长度
	for (int i = n - 1; i >= 0; i--)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (s[i] == s[j])
			{
				dp[i][j] = dp[i + 1][j - 1] + 2;
			}
			else
			{
				dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
			}
		}
	}

	return dp[0][n - 1];
}

//0-1背包问题
int knapsack(int W, int N, vector<int>& wt, vector<int>& val)
{
	vector<vector<int>> dp(N + 1, vector<int>(W + 1, 0));
	//dp[i][w]表示对于前i个物品当前背包容量为w时，能够装下的最大价值
	for (int i = 1; i <= N; i++)
	{
		for (int w = 1; w <= W; w++)
		{
			if (w - wt[i - 1] < 0)
			{
				dp[i][w] = dp[i - 1][w];
			}
			else
			{
				dp[i][w] = max(dp[i - 1][w],
					dp[i - 1][w - wt[i - 1]] + val[i - 1]);
			}
		}
	}
	return dp[N][W];
}

int knapsack_2(int W, int N, vector<int>& wt, vector<int>& val)//等待用回溯重写一下
{
	vector<int> dp(W + 1, 0);
	for (int i = 0; i < dp.size(); i++)
	{
		for (int j=0;j<N;j++)
		{
			if (i - wt[j] < 0) continue;
			dp[i] = max(dp[i], dp[i - wt[j]] + val[j]);
		}
	}
	return dp[W];
}

//416分割等和子集
//给你一个 只包含正整数 的 非空 数组 nums 。请你判断是否可以将这个数组分割成两个子集，使得两个子集的元素和相等。
bool canPartition(vector<int>& nums) {
	int sum = 0;
	for (int num : nums) sum += num;
	if (sum % 2 != 0)return false;
	int n = nums.size();
	sum = sum / 2;
	vector<vector<bool>> dp(n + 1, vector<bool>(sum + 1, false));
	for (int i = 0; i <= n; i++)
	{
		dp[i][0] = true;
	}

	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= sum; j++)
		{
			if (j - nums[i - 1] < 0)
			{
				dp[i][j] = dp[i - 1][j];
			}
			else
			{
				dp[i][j] = dp[i - 1][j] || dp[i - 1][j - nums[i - 1]];
			}
		}
	}
	return dp[n][sum];
}

//完全背包问题
int change(int amount, vector<int> coins)
{
	int n = coins.size();
	vector<vector<int>> dp(n + 1, vector<int>(amount + 1, 0));
	
	for (int i = 0; i <= n; i++)
		dp[i][0] = 1;

	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= amount; j++)
		{
			if (j - coins[i - 1] >= 0)
			{
				dp[i][j] = dp[i - 1][j] + dp[i][j - coins[i - 1]];
			}
			else
			{
				dp[i][j] = dp[i - 1][j];
			}
			
		}
	}
	return dp[n][amount];
}

//719K 站中转内最便宜的航班
unordered_map<int, vector<vector<int>>> indegree;//key-目的地 value-[出发地，票钱]
static int g_src = 0;
static int g_dst = 0;

int dp(int s, int k, vector<vector<int>> &mem)
{
	if (s == g_src)
		return 0;
	if (k == 0)
		return -1;
	if (mem[s][k] != -888)
		return mem[s][k];

	int res = INT_MAX;
	if (indegree.find(s) != indegree.end())
	{
		for (auto& v : indegree[s])
		{
			int from = v[0];
			int price = v[1];

			int subProblem = dp(from, k - 1, mem);
			if (subProblem != -1)
			{
				res = min(res, subProblem + price);
			}
		}
	}
	res == INT_MAX ? -1 : res;
	mem[s][k] = res;
	return mem[s][k];
}
int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {

	k++;
	g_src = src;
	g_dst = dst;
	for (auto& f : flights)
	{
		int from = f[0];
		int to = f[1];
		int price = f[2];
		vector<int> group{ f[0],f[2] };
		indegree[f[1]].push_back(group);
	}
	int count = flights.size();
	vector<vector<int>> mem(count, vector<int>(k+1, -888));
	return dp(dst, k, mem);
}

void test_719()
{
	int n = 3;
	int src = 0, dst = 2;
	int k = 0;
	vector<vector<int>> flights;
	flights.push_back(vector<int>{0, 1, 100});
	flights.push_back(vector<int>{1, 2, 100});
	flights.push_back(vector<int>{0, 2, 500});
	int res = findCheapestPrice(n, flights, src, dst, k);
	cout << "res=" << res;
}
//10. 正则表达式匹配
bool isMatch(string s, string p) {
	int m = s.size();
	int n = p.size();

	auto matches = [&](int i, int j) {
		if (i == 0) return false;
		if (p[j - 1] == '.') return true;
		return s[i - 1] == p[j - 1];
	};
	vector<vector<bool>> f(m + 1, vector<bool>(n + 1, false));
	f[0][0] = true;
	for (int i = 0; i <= m; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (p[j - 1] == '*')
			{
				f[i][j] = f[i][j - 2];
				if (matches(i, j - 1))
				{
					f[i][j] = f[i][j] || f[i - 1][j];
				}

			}
			else
			{
				if (matches(i, j))
				{
					f[i][j] = f[i - 1][j - 1];
				}
			}
		}
	}
	return f[m][n];
}

//312戳气球
int maxCoins(vector<int>& nums) {
	int n = nums.size();
	vector<int> points(n + 2, 1);
	for (int i = 0; i < n; i++)
	{
		points[i + 1] = nums[i];
	}

	//定义dp[i][j]为在(i,j)范围内选择最后扎破第k个气球获取到的最大金额
	//dp[i][j]=dp[i][k]+dp[k][j]+nums[k]*nums[i]*nums[j]

	vector<vector<int>> dp(n + 2, vector<int>(n + 2, 0));
	for (int i = n+1; i >=0 ;i--)
	{
		for (int j=i+1;j<=n+1;j++)
		{
			for (int k = i + 1; k < j; k++)
			{
				dp[i][j] = max(dp[i][j],
					dp[i][k] + dp[k][j] + points[k] * points[i] * points[j]);
			}
		}
	}
	return dp[0][n + 1];
}

void test_312()
{
	vector<int> v{ 3,1,5,8 };
	int res = maxCoins(v);
	cout << "res=" << res << endl;
}

