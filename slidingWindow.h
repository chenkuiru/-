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