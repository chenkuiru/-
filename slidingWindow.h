#pragma once
//滑动窗口算法
#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

string minWindow(string s, string t)
{
	unordered_map<char, int> need, window;
	for (char c : t) need[c]++;

	int left = 0, right = 0;
	int valid = 0;
	int start = 0, len = INT_MAX;
	while (right < s.size())
	{
		char c = s[right];
		right++;
		if (need.count(c))
		{
			window[c]++;
			if (window[c] == need[c])
				valid++;
		}

		printf("window:[%d, %d)\n", left, right);
		//窗口开始收缩
		while (valid == need.size())
		{
			if (right - left < len)
			{
				start = left;
				len = right - left;
			}
			//删除窗口最左侧的字符
			char d = s[left];
			//左移窗口
			left++;
			if (need.count(d))
			{
				if (window[d] == need[d])
				{
					valid--;
				}
				window[d]--;
			}
		}
	}

	return len == INT_MAX ? "" : s.substr(start, len);

}

void testNo76()
{
	string s = "ADOBECODEBANC", t = "ABC";
	auto res = minWindow(s, t);
	cout << "res = " << res << endl;
}
//3无重复字符的最长子串
int lengthOfLongestSubstring(string s) {
	int left = 0, right = 0;
	unordered_map<char, int> window;
	int res = 0;
	int len = s.size();
	while (right < len)
	{
		char c = s[right];
		window[c]++;
		right++;

		while (window[c] > 1)
		{
			char t = s[left];
			left++;
			window[t]--;
		}
		res = max(res, right - left);

	}
	return res;
}

void testlt3()
{
	string s = "pwwkew";
	int res = lengthOfLongestSubstring(s);
}


//1004最大连续1的个数
int longestOnes(vector<int>& nums, int k) {
	int len = nums.size();
	if (len == 0) return 0;
	int left = 0, right = 0;
	int ans = 0, sum = 0;
	while (right < len)
	{
		if (nums[right] == 0)
			sum++;
		while (sum > k)
		{
			if (nums[left] == 0)
				sum--;
			left++;
		}
		ans = max(ans, right - left + 1);
		right++;
	}
	return ans;
}

void test1004()
{
	vector<int> v{ 1,1,1,0,0,0,1,1,1,1,0 };
	int num = longestOnes(v, 2);
	cout << "ok" << endl;
}

//2024考试的最大困扰度
int maxConsecutiveAnswers_helper(string answerKey, int k, char c) {
	int left = 0, right = 0;
	int sum = 0;
	int ans = 0;
	int len = answerKey.size();
	while (right < len)
	{
		if (answerKey[right] != c)
			sum++;
		while (sum > k)
		{
			if (answerKey[left] != c)
			{
				sum--;
			}
			left++;
				
		}
		ans = max(ans, right - left + 1);
		right++;
	}
	return ans;
}
int maxConsecutiveAnswers(string answerKey, int k) {
	return max(maxConsecutiveAnswers_helper(answerKey, k, 'T'),
		maxConsecutiveAnswers_helper(answerKey, k, 'F'));
}

void test2024()
{
	string s = "TTFTTFTT";
	int res = maxConsecutiveAnswers(s, 1);
	cout << "res = " << res << endl;
}