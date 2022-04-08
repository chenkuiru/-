#pragma once
#include <iostream>
#include <vector>
#include <math.h>
#include "parameters.h"

using namespace std;

void merge(vector<int> &arrays, int L, int M, int R)
{
	vector<int> tmp(R - L + 1);
	int left = L;
	int right = M+1;
	int t = 0;
	while (left <= M && right <= R)
	{
		if (arrays[left] < arrays[right])
		{
			tmp[t] = arrays[left];
			t++;
			left++;
		}
		else
		{
			tmp[t] = arrays[right];
			t++;
			right++;
		}
	}

	while (left <= M)
	{
		tmp[t] = arrays[left];
		t++;
		left++;
	}

	while (right <= R)
	{
		tmp[t] = arrays[right];
		t++;
		right++;
	}

		//把临时数组的值替换到原数组中
		t = 0;
		while (L <= R)
		{
			arrays[L++] = tmp[t++];
		}
	

}
//归并排序算法(自顶而下）
void mergeSort(vector<int> &arrays, int L, int R)
{
	if (L == R)
		return;
	int M = (L + R) / 2;
	mergeSort(arrays, L, M);
	mergeSort(arrays, M + 1, R);
	merge(arrays, L, M, R);
}



//void mergeSort_2(vector<int>& arrays)
//{
//	int length = arrays.size();
//	vector<int> tmp(length);
//	int index = 0;
//	for (int len = 1; len < length; len <<= 1)
//	{
//		int left_min = 0, left_max = 0, right_min = 0, right_max = 0;
//		for (left_min = 0; left_min < length - len; left_min = right_max)
//		{
//			right_min = left_max = left_min + len;
//			right_max = left_max + len;
//			if (right_max > length)
//			{
//				right_max = length;
//			}
//			index = 0;
//			while (left_min < left_max && right_min < right_max)
//			{
//				if (arrays[left_min] < arrays[right_min])
//				{
//					tmp[index++] = arrays[left_min++];
//				}
//				else
//				{
//					tmp[index++] = arrays[right_min++];
//				}
//			}
//			while (left_min < left_max)
//			{
//				tmp[index++] = arrays[left_min++];
//			}
//			while (right_min < right_max)
//			{
//				tmp[index++] = arrays[right_min++];
//			}
//			if()
//
//
//		}
//	}
//}


//快速排序
int Partition(vector<int>& arrays, int L, int R)
{
	int pivotValue = arrays[L];
	while (L < R)
	{
		while (L < R && arrays[R] >= pivotValue)
			R--;
		swap(arrays[L], arrays[R]);
		while (L < R && arrays[L] <= pivotValue)
			L++;
		swap(arrays[L], arrays[R]);

	}
	return L;
}
void quicksort(vector<int>& arrays, int L, int R)
{
	if (L >= R)return;
	int pivot = Partition(arrays, L, R);
	quicksort(arrays, L, pivot - 1);
	quicksort(arrays, pivot + 1, R);

}

//冒泡排序
void BubbleSort(vector<int>& arrays)
{
	int len = arrays.size();
	for (int i = 0; i <len; i++)
	{
		for (int j = len - 1; j > i; j--)
		{
			if (arrays[j] < arrays[j - 1])
			{
				swap(arrays[j], arrays[j - 1]);
			}
		}
	}
}
//插入排序
void InsertSort(vector<int>& arrays)
{
	int len = arrays.size();
	for (int i = 1; i < len; i++)
	{
		int pre = i - 1, cur = i;
		while (arrays[cur] < arrays[pre] && pre >= 0 )
		{
			swap(arrays[cur], arrays[pre]);
			pre--;
			cur--;
		}
	}
}

void test_mergeSort()
{
	vector<int> v{ 1,4,5,7,9,2 };
	quicksort(v, 0, 5);
	//InsertSort(v);
	for (auto a : v)
	{
		cout << a << endl;
	}

}

//287寻找重复数
int findDuplicate(vector<int>& nums) {
	int target = -1;
	int left = 1;
	int right = nums.size() - 1;
	while (left <= right)
	{
		int mid = (left + right) / 2;
		int sum = 0;
		for (int i = 0; i < nums.size(); i++)
		{
			if (nums[i] <=mid)
				sum++;
		}
		if (sum <= mid)
		{
			left = mid+1;
		}
		else
		{
			right = mid - 1;
		}
	}
	target = left;
	return target;
}
void test287()
{
	vector<int> v{ 1,3,4,2,2 };
	auto res = findDuplicate(v);
	cout << res << endl;
}

class MedianFinder {
public:
	MedianFinder() {

	}

	void addNum(int num) {
		numlist.push_back(num);
		sort(numlist.begin(), numlist.end(), [](int a, int b) {return a < b; });
	}

	double findMedian() {
		int len = numlist.size();
		if (len == 0) return 0;
		int index = 0;
		if (len % 2 != 0)
		{
			index = len / 2;
			return numlist[index];
		}
		else
		{
			index = len / 2 - 1;
			return (numlist[index] + numlist[index + 1]) / 2.0;
		}
	}
private:
	vector<int> numlist;
};

void test295()
{
	MedianFinder m;
	m.addNum(1);
	m.addNum(2);
	auto res = m.findMedian();
	m.addNum(3);
	res = m.findMedian();
}

