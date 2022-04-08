#pragma once
//回溯算法
#include <iostream>
#include <vector>

using namespace std;
//2028找出缺失的观测数据
vector<int> res2028;
bool checkvalue(int target, vector<int>& path)
{
	bool res = false;
	int sum = 0;
	for (auto t : path)
	{
		sum += t;
	}
	res = sum == target ? true : false;
	return res;
}
void missingRolls_bt(int target, int n, vector<int>& path)
{
	if (path.size() == n)
	{
		if (checkvalue(target, path))
		{
			res2028 = path;
			return;
		}
		return;
	}

	for (int i = 1; i < 7; i++)
	{
		path.push_back(i);
		missingRolls_bt(target, n, path);
		path.pop_back();
	}
}
vector<int> missingRolls(vector<int>& rolls, int mean, int n) {
	int len = rolls.size();
	if (len == 0) return res2028;
	int rollsum = 0;
	for (auto t : rolls)
	{
		rollsum += t;
	}
	int target = (len+n) * mean - rollsum;
	vector<int> path;

	missingRolls_bt(target, n, path);
	return res2028;
}

void test2028()
{
	vector<int> rolls{ 3,2,4,3 };
	auto resv = missingRolls(rolls, 4, 2);
	cout << "res = " << endl;
}


class Solution_2028 {
public:
	vector<int> missingRolls(vector<int>& rolls, int mean, int n) {
		int m = rolls.size();
		int sum = mean * (n + m);
		int missingSum = sum;
		for (int& roll : rolls) {
			missingSum -= roll;
		}
		if (missingSum < n || missingSum > 6 * n) {
			return {};
		}
		int quotient = missingSum / n, remainder = missingSum % n;
		vector<int> missing(n);
		for (int i = 0; i < n; i++) {
			missing[i] = quotient + (i < remainder ? 1 : 0);
		}
		return missing;
	}
};
