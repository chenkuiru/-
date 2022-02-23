#pragma once
//���������㷨
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
		//���ڿ�ʼ����
		while (valid == need.size())
		{
			if (right - left < len)
			{
				start = left;
				len = right - left;
			}
			//ɾ�������������ַ�
			char d = s[left];
			//���ƴ���
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