#pragma once
//链表,数组，
//左右指针
#include <iostream>
#include <vector>
#include <math.h>
#include "parameters.h"

using namespace std;



	
	//2.两数相加
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		if (l1 == nullptr || l2 == nullptr) return nullptr;
		ListNode* out = new ListNode();
		ListNode* current = out;
		int add = 0;
		while (l1 != nullptr && l2 != nullptr)
		{
			int sum = l1->val + l2->val + add;
			if (sum < 10)
			{
				add = 0;
			}
			else
			{
				sum = sum % 10;
				add = 1;
			}
			ListNode* nextNode = new ListNode(sum);
			current->next = nextNode;
			l1 = l1->next;
			l2 = l2->next;
			current = current->next;
		}

		if (l1 == nullptr)
		{
			while (l2)
			{
				int value = l2->val + add;
				if (value < 10)
				{
					add = 0;
				}
				else
				{
					value = 0;
					add = 1;
				}
				ListNode* nextNode = new ListNode(value);
				current->next = nextNode;
				l2 = l2->next;
				current = current->next;
			}
		}

		if (l2 == nullptr)
		{
			while (l1)
			{
				int value = l1->val + add;
				if (value < 10)
				{
					add = 0;
				}
				else
				{
					value = 0;
					add = 1;
				}
				ListNode* nextNode = new ListNode(value);
				current->next = nextNode;
				l1 = l1->next;
				current = current->next;
			}
		}

		if (add != 0)
		{
			ListNode* nextNode = new ListNode(1);
			current->next = nextNode;
		}
		return out->next;

	}

	void testNo2()
	{
		ListNode* Node1 = new ListNode(5);
		ListNode* Node2 = new ListNode(9);
		//ListNode* Node3 = new ListNode(3);
		Node1->next = Node2;
		//Node2->next = Node3;
		ListNode* Node4 = new ListNode(5);
		/*ListNode* Node5 = new ListNode(6);
		ListNode* Node6 = new ListNode(4);
		Node4->next = Node5;
		Node5->next = Node6;*/

		auto Node = addTwoNumbers(Node1, Node4);
		
		while (Node)
		{
			cout << "Node->val = " << Node->val << endl;
			Node = Node->next;
		}
	}


//11盛水最多的容器
int calArea(vector<int>& height, int leftIndex, int rightIndex)
{
	int h = min(height[leftIndex], height[rightIndex]);
	int w = rightIndex - leftIndex;
	return (h * w);
}

int maxArea(vector<int>& height) {
	int maxValue = 0;
	if (height.size() == 0) return maxValue;
	int left = 0, right = height.size() - 1;
	bool leftmove = true, rightmove = true;
	while (left < right)
	{
		int Area = calArea(height, left, right);
		if (Area > maxValue)maxValue = Area;
		cout << "maxValue=" << maxValue << endl;
		if (height[left] > height[right])
		{
			right--;
		}
		else
		{
			left++;
		}
	}
	return maxValue;
	}

void testNo11()
{
	vector<int> test{ 2,3,10,5,7,8,9 };
	int res = maxArea(test);
	cout << "res=" << res << endl;
}

//15三数之和
vector<vector<int>> threeSum(vector<int>&nums) {
		vector<vector<int>> ans;
		int n = nums.size();
		std::sort(nums.begin(), nums.end());
		for (int first = 0; first < n; ++first)
		{
			if (first > 0 && nums[first] == nums[first - 1])
				continue;
			int target = -nums[first];
			int third = n - 1;
			for (int second = first + 1; second < n; ++second)
			{
				if (second > first + 1 && nums[second] == nums[second - 1])
					continue;

				while (second < third && nums[second] + nums[third] > target)
				{
					third--;
				}

				if (second == third)
					break;

				if (nums[second] + nums[third] == target) {
					ans.push_back({ nums[first], nums[second], nums[third] });
				}


			}

		}
		return ans;
}

//16 最接近三数之和
int threeSumClosest(vector<int>& nums, int target) {
	int n = nums.size();
	std::sort(nums.begin(), nums.end());
	vector<int> res;
	int distance = INT_MAX;
	int sum = 0;
	for (int first = 0; first < n; ++first)
	{
		int aim = target-nums[first];
		int third = n - 1;
		int second = first + 1;
		if (second >= third)
			continue;

			while (second < third )
			{
				int temp = std::abs(nums[second] + nums[third] - aim);
				if (temp < distance)
				{
					distance = temp;
					sum = nums[first] + nums[second] + nums[third];

				}
				if (nums[second] + nums[third] > aim)
					third--;
				else
					second++;
			}

	}

	return sum;
}

void testNo16()
{
	vector<int> test{ -4,-1,1,2 };
	int res = threeSumClosest(test, 1);
	cout << "res = " << res << endl;
}

//18四数之和
vector<vector<int>> fourSum(vector<int>& nums, int target) {
	vector<vector<int>> quadruplets;
	if (nums.size() < 4) {
		return quadruplets;
	}
	sort(nums.begin(), nums.end());
	int length = nums.size();
	for (int i = 0; i < length - 3; i++) {
		if (i > 0 && nums[i] == nums[i - 1]) {
			continue;
		}
		if ((long)nums[i] + nums[i + 1] + nums[i + 2] + nums[i + 3] > target) {
			break;
		}
		if ((long)nums[i] + nums[length - 3] + nums[length - 2] + nums[length - 1] < target) {
			continue;
		}
		for (int j = i + 1; j < length - 2; j++) {
			if (j > i + 1 && nums[j] == nums[j - 1]) {
				continue;
			}
			if ((long)nums[i] + nums[j] + nums[j + 1] + nums[j + 2] > target) {
				break;
			}
			if ((long)nums[i] + nums[j] + nums[length - 2] + nums[length - 1] < target) {
				continue;
			}
			int left = j + 1, right = length - 1;
			while (left < right) {
				int sum = nums[i] + nums[j] + nums[left] + nums[right];
				if (sum == target) {
					quadruplets.push_back({ nums[i], nums[j], nums[left], nums[right] });
					while (left < right && nums[left] == nums[left + 1]) {
						left++;
					}
					left++;
					while (left < right && nums[right] == nums[right - 1]) {
						right--;
					}
					right--;
				}
				else if (sum < target) {
					left++;
				}
				else {
					right--;
				}
			}
		}
	}
	return quadruplets;
}

//21合并两个有序链表
ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
	ListNode* head = new ListNode(0);
	auto tmp = head;

	while (list1 && list2)
	{
		if (list1->val <= list2->val)
		{
			head->next = list1;
			list1 = list1->next;
		}
		else
		{
			head->next = list2;
			list2 = list2->next;
		}
		head = head->next;
	}
	
	head->next = list1 == nullptr ? list2 : list1;
	
	return tmp->next;
}

void testlt21()
{
	ListNode* no1 = new ListNode(1);
	ListNode* no2 = new ListNode(2);
	ListNode* no3 = new ListNode(4);
	ListNode* no4 = new ListNode(1);
	ListNode* no5 = new ListNode(3);
	ListNode* no6 = new ListNode(4);
	no1->next = no2;
	no2->next = no3;
	no4->next = no5;
	no5->next = no6;

	auto res = mergeTwoLists(nullptr, nullptr);
	cout << "res = " << endl;
}

//27原地移除元素某个指定元素
int removeElement(vector<int>& nums, int val) {
	if (nums.size() == 0) return 0;
	int slow = 0, fast = 0;
	while (fast < nums.size())
	{
		if (nums[fast] != val)
		{
			if (slow != fast)
			{
				nums[slow] = nums[fast];
			}
			slow++;
		}
		fast++;
	}

	return slow;
}

void testNo27()
{
	vector<int> nums{ 0,1,2,2,3,0,4,2 };
	int res = removeElement(nums, 2);
	cout << "res= " << res << endl;
}

//28实现strStr()给你两个字符串 haystack 和 needle ，请你在 haystack 字符串中找出 
//needle 字符串出现的第一个位置（下标从 0 开始）。如果不存在，则返回  -1 。
int strStr(string haystack, string needle) {
	int length1 = haystack.length();
	int length2 = needle.length();
	if (length2 == 0)return 0;
	int p1 = 0, p2 = 0;
	while (p1 < length1)
	{
		if (haystack.substr(p1,length2)==needle)
		{
			break;
		}
		p1++;
	}
	if (p1 == length1)
		return -1;
	return p1;

}

void testNo28()
{
	string str1 = "aaaaa";
	string str2 = "baa";
	int res = strStr(str1, str2);
	cout << "res= " << res << endl;
}

//使用kmp算法解决28题
int strStr_KMP(string haystack, string needle)
{
	int needleLength = needle.length();
	if (needleLength == 0) return 0;

	//计算next数组
	vector<int> next(needleLength);
	for (int right = 1, left = 0; right < needleLength; right++)
	{
		while (left > 0 && needle[left] != needle[right])
		{
			left = next[left - 1];
		}
		if (needle[left] == needle[right])
			left++;
		next[right] = left;
	}

	for (int i = 0, j = 0; i < haystack.length(); i++)
	{
		while (j > 0 && haystack[i] != needle[j])
		{
			j = next[j - 1];
		}
		if (haystack[i] == needle[j])
			j++;
		if (j == needleLength)
			return i - needleLength + 1;
	}
	return -1;
}

//用动态规划实现kmp

int strStr_DP(string haystack, string needle)
{
	int hayLength = haystack.length();
	int needLength = needle.length();
	vector<vector<int>> dp(needLength, vector<int>(256));

	dp[0][needle[0]] = 1;
	int X = 0;
	for (int j = 1; j < needLength; j++) {
		for (int c = 0; c < 256; c++)
			dp[j][c] = dp[X][c];
		dp[j][needle[j]] = j + 1;
		// 更新影子状态
		X = dp[X][needle[j]];
	}

	int j = 0;
	for (int i = 0; i < hayLength; i++) {
		j = dp[j][haystack[i]];
		// 到达终止态，返回结果
		if (j == needLength) return i - needLength + 1;
	}
	return -1;

}

//31下一个字典序排列
void nextPermutation(vector<int>& nums) {
	int length = nums.size();
	if (length < 2)return;
	int rightIndex = length - 1;
	int leftIndex = length - 2;
	while (nums[leftIndex] >= nums[rightIndex])
	{
		leftIndex--;
		rightIndex--;
		if (leftIndex < 0)
			break;
	}

	int left = 0, right = length - 1;
	if (leftIndex > -1)
	{
		int targetIndex = length - 1;
		while (nums[targetIndex] <= nums[leftIndex] && targetIndex  > leftIndex)
		{
			targetIndex--;
		}

		int temp = nums[leftIndex];
		nums[leftIndex] = nums[targetIndex];
		nums[targetIndex] = temp;
		left = leftIndex + 1;
		right = length - 1;
	}
	while (left < right)
	{
		std::swap(nums[left], nums[right]);
		left++;
		right--;
	}
}

void testNo31()
{
	vector<int> v1{ 4,3,2,1 };
	nextPermutation(v1);

	cout << "res:" << endl;
	for (auto a : v1)
	{
		cout << a << endl;
	}
}

//42接雨水
int trap(vector<int>& height) {
	int area = 0;
	if (height.size() == 0) return 0;
	int maxHindex = 0;
	int maxvalue = 0;
	for (int i = 0; i < height.size(); i++)
	{
		if (height[i] > maxvalue)
		{
			maxvalue = height[i];
			maxHindex = i;
		}
	}
	int left = 0, right = 1;
	
	
	int valuesum = 0;
	bool bret = false;
	while (left < maxHindex)
	{
		valuesum = 0;
		while (height[left] > height[right])
		{
				valuesum += height[right];
				right++;
				bret = true;
		}
		if (bret)
		{
			int temp = height[left] * (right - left) - valuesum - height[left];
			area += temp;
			left = right;
			right++;
		}
		else
		{
			left++;
			right++;
		}
		
	}
	right = height.size() - 1;
	left = right - 1;
	bret = false;
	while (right > maxHindex)
	{
		valuesum = 0;
		while (height[right] > height[left])
		{
			valuesum += height[left];
			left--;
			bret = true;
		}
		if (bret)
		{
			int temp = height[right] * (right - left) - valuesum - height[right];
			area += temp;
			right = left;
			left--;
		}
		else
		{
			left--;
			right--;
		}
		
	}
	return area;
}

void testNo42()
{
	vector<int> v{ 2,0,2 };
	int res = trap(v);
	cout << "res= " << res << endl;
}

int trap_ans(vector<int>& height) {
	int ans = 0;
	int left = 0, right = height.size() - 1;
	int leftMax = 0, rightMax = 0;
	while (left < right) {
		leftMax = max(leftMax, height[left]);
		rightMax = max(rightMax, height[right]);
		if (height[left] < height[right]) {
			ans += leftMax - height[left];
			++left;
		}
		else {
			ans += rightMax - height[right];
			--right;
		}
	}
	return ans;
}
//61 旋转链表
ListNode* rotateRight(ListNode* head, int k) {
	if (head == nullptr || k < 0)return nullptr;
	if (k == 0) return head;
	int count = 1;
	ListNode* res = head;
	ListNode* slow = head;
	ListNode* fast = head;
	for (int i = 0; i < k; i++)
	{
		if (fast->next != nullptr)
		{
			fast = fast->next;
			count++;
		}
		else
			break;
	}
	if (count == 1|| k % count == 0) return head;

	if (k > count)
	{
		fast = head;
		for (int i = 0; i < k % count; i++)
		{
			fast = fast->next;
		}
	}

	while (fast->next != nullptr)
	{
		fast = fast->next;
		slow = slow->next;
	}
	res = slow->next;
	slow->next = nullptr;
	fast->next = head;
	return res;
}

void testNo61()
{
	ListNode* head = new ListNode(1);
	ListNode* no2 = new ListNode(2);
	ListNode* no3 = new ListNode(3);
	ListNode* no4 = new ListNode(4);
	ListNode* no5 = new ListNode(5);
	head->next = no2;
	no2->next = no3;
	no3->next = no4;
	no4->next = no5;
	auto res = rotateRight(head, 2);
	while (res->next)
	{
		cout << res->val << endl;
		res = res->next;
	}
}

//75颜色分类
void sortColors(vector<int>& nums) {
	if (nums.size() == 0)return;
	unordered_map<int, int> Countmap;
	list<int> num;
	for (auto it : nums)
	{
		if (Countmap.find(it) != Countmap.end())
		{
			Countmap[it]++;
		}
		else
		{
			Countmap.insert(pair<int,int>(it, 1));
			num.push_back(it);
		}
	}
	num.sort();
	vector<int> res;
	int length = num.size();
	for (int i = 0; i < length; i++)
	{
		int value = num.front();
		num.pop_front();
		for (int j = 0; j < Countmap[value]; j++)
		{
			res.push_back(value);
		}
	}
	nums = res;
}

void testNo75()
{
	vector<int> v{ 1,2,0,1,2,0 };
	sortColors(v);
}

//80 删除有序数组中的重复项 II
int removeDuplicates_ans(vector<int>& nums) {
	int n = nums.size();
	if (n <= 2) {
		return n;
	}
	int slow = 2, fast = 2;
	while (fast < n) {
		if (nums[slow - 2] != nums[fast]) {
			nums[slow] = nums[fast];
			++slow;
		}
		++fast;
	}
	return slow;

}

//82  删除排序链表中的重复元素 II
ListNode* deleteDuplicates(ListNode* head) {
	if (head == nullptr || head->next==nullptr) return head;
	ListNode* target = new ListNode(0,head);
	ListNode* slow = target;
	while (slow->next && slow->next->next)
	{

		if (slow->next->val == slow->next->next->val)
		{
			int value = slow->next->val;
			while (slow->next && slow->next->val == value)
				slow->next = slow->next->next;
		}
		else
		{
			slow = slow->next;
		}
	}
	return target->next;
}

//86 分割链表
ListNode* partition(ListNode* head, int x) {
	if (head == nullptr) return head;
	ListNode* dummy1 = new ListNode(0);
	ListNode* p1 = dummy1;
	ListNode* dummy2 = new ListNode(0);
	ListNode* p2 = dummy2;
	while (head)
	{
		if (head->val < x)
		{
			p1->next = head;
			p1 = p1->next;
		}
		else
		{
			p2->next = head;
			p2 = p2->next;
		}
		head = head->next;
	}
	p2->next = nullptr;
	p1->next = dummy2->next;

	return dummy1->next;
}

void testNo86()
{
	ListNode* head = new ListNode(1);
	ListNode* no2 = new ListNode(3);
	ListNode* no3 = new ListNode(3);
	ListNode* no4 = new ListNode(2);
	ListNode* no5 = new ListNode(5);
	head->next = no2;
	no2->next = no3;
	no3->next = no4;
	no4->next = no5;
	auto res = partition(head, 3);
	while (res)
	{
		cout << res->val << endl;
		res = res->next;
	}
}

//88 合并两个有序链表
void merge_an88(vector<int>& nums1, int m, vector<int>& nums2, int n) {
	int p1 = m - 1, p2 = n - 1;
	int tail = m + n - 1;
	int cur;
	while (p1 >= 0 || p2 >= 0) {
		if (p1 == -1) {
			cur = nums2[p2--];
		}
		else if (p2 == -1) {
			cur = nums1[p1--];
		}
		else if (nums1[p1] > nums2[p2]) {
			cur = nums1[p1--];
		}
		else {
			cur = nums2[p2--];
		}

		nums1[tail--] = cur;
	}
}

//141.环形链表
bool hasCycle(ListNode* head) {
	if (head == nullptr || head->next == nullptr)return false;
	auto slow = head;
	auto fast = head;
	while (fast->next && fast->next->next)
	{
		slow = slow->next;
		fast = fast->next->next;
		if (slow == fast)
			return true;
	}
	return false;
}


//457环形数组
bool circularArrayLoop(vector<int>& nums) {
	int len = nums.size();
	if (len < 2) return false;
	int originIndex = 0, newIndex = 0;
	for (int i = 0; i < nums.size(); i++)
	{
		originIndex = i;
		int value = nums[originIndex] > 0 ? nums[originIndex] : nums[originIndex] % len + len;
		newIndex = (value + originIndex) % len;
		if (originIndex == newIndex) continue;

		int tmp = originIndex;
		//bool flag = true;
		int k = 1;
		while (true)
		{
			if (k > len) break;
			if (originIndex == newIndex)
			{
				if (k > 1)
					return true;
				else
					break;
			}
			if (nums[tmp] * nums[newIndex] < 0 || tmp == newIndex)
			{
				//flag = false;
				break;
			}
			tmp = newIndex;
			int value = nums[newIndex] > 0 ? nums[newIndex] : nums[newIndex] % len + len;
			newIndex = (value + newIndex) % len;
			k++;
		}
		/*if (flag)
			return true;*/
	}
	return false;
}

bool circularArrayLoop_ans(vector<int>& nums) {
		int n = nums.size();
		auto next = [&](int cur) {
			return ((cur + nums[cur]) % n + n) % n; // 保证返回值在 [0,n) 中
		};

		for (int i = 0; i < n; i++) {
			if (!nums[i]) {
				continue;
			}
			int slow = i, fast = next(i);
			// 判断非零且方向相同
			while (nums[slow] * nums[fast] > 0 && nums[slow] * nums[next(fast)] > 0) 
			{
				if (slow == fast) {
					if (slow != next(slow)) {
						return true;
					}
					else {
						break;
					}
				}
				slow = next(slow);
				fast = next(next(fast));
			}
			int add = i;
			while (nums[add] * nums[next(add)] > 0) {
				int tmp = add;
				add = next(add);
				nums[tmp] = 0;
			}
		}
		return false;
}

void test_457()
{
	vector<int> v{ -1,2 };
	bool res = circularArrayLoop(v);
	cout << res << endl;
}

//475 供暖器
bool heatHouse(vector<int>& houses, vector<int>& heaters, int R)
{
	int rightmax = max(houses.back(),heaters.back());
	for (int i = 0; i < houses.size(); i++)
	{
		int left = (houses[i] - R > 1)? houses[i] - R : 1;
		int right = (houses[i] + R < rightmax)? houses[i] + R: rightmax;
		int sum = 0;
		for (int j = 0; j < heaters.size(); j++)
		{
			if (heaters[j]<left || heaters[j]>right)
			{
				sum ++;
				continue;
			}
			else
				break;
		}
		
	}
	return true;
}
int findRadius(vector<int>& houses, vector<int>& heaters)
{
	int n = houses.size(), m = heaters.size();
	int maxR = max(houses.back(),heaters.back()) - 1;
	int minR = 0;
	for (; minR <= maxR; minR++)
	{
		if (heatHouse(houses, heaters, minR))
			break;
	}
	return minR;

}
void test_475()
{
	vector<int> houses{ 1 };
	vector<int> heaters{ 1 ,4};
	int r = findRadius(houses, heaters);
	cout << r << endl;
}
//最短无序子数组
int findUnsortedSubarray(vector<int>& nums) {
	if (is_sorted(nums.begin(), nums.end())) return 0;
	vector<int> sortnums(nums);
	sort(sortnums.begin(), sortnums.end());
	int left = 0;
	int right = nums.size()-1;
	while (sortnums[left] == nums[left])
	{
		left++;
	}
	while (sortnums[right] == nums[right])
	{
		right--;
	}
	return right - left + 1;
}

//524. 通过删除字母匹配到字典里最长单词
bool isSubstr(string& origin, string& child)
{
	int j = 0;
	for (int i = 0; i < origin.length(); i++)
	{
		if (origin[i] == child[j])
		{
			j++;
		}
	}
	if (j == child.length())
		return true;
	else
		return false;
	
}
string findLongestWord(string s, vector<string>& dictionary) {
	if (dictionary.size() == 0) return "";
	auto sortfunc = [](string& a, string& b) {
		if (a.length() == b.length())
		{
			return a < b;
		}
		else
		{
			return a.length() > b.length();
		}
	};
	sort(dictionary.begin(), dictionary.end(), sortfunc);

	for (auto& tmp : dictionary)
	{
		if (isSubstr(s, tmp))
			return tmp;
	}

	return "";
}

//522. 最长特殊序列 II
int findLUSlength(vector<string>& strs) {
	sort(strs.begin(), strs.end(), [](string a, string b) {//按照长度从大到小排 
		return a.size() > b.size();
	});
	for (int i = 0; i < strs.size(); i++) {//按照长度从大到小枚举串i 判断i会否是特殊序列
		bool isSub = false;//先假设i不是任何串的子串
		for (int j = 0; j < strs.size() && strs[i].size() <= strs[j].size(); j++) {//判断i是否为j的子串
			if (i != j && isSubstr(strs[j], strs[i])) {//若i是j的子串 则i不是特殊序列 跳出即可 
				isSub = true;
				break;
			}
		}
		if (!isSub) return strs[i].size();//i不是任何串的子串 则为特殊序列 直接返回即可 
	}
	return -1;
}

//1721. 交换链表中的节点
ListNode* swapNodes(ListNode* head, int k) {
	if (head == nullptr || head->next == nullptr) return head;
	auto slow = head, fast = head;
	for (int i = 0; i < k - 1; i++)
	{
		fast = fast->next;
	}
	int smallValue = fast->val;
	while (fast->next != nullptr)
	{
		fast = fast->next;
		slow = slow->next;
	}
	int maxValue = slow->val;
	slow->val = smallValue;

	auto tmp = head;
	for (int i = 0; i < k - 1; i++)
	{
		tmp = tmp->next;
	}
	tmp->val = maxValue;
	return head;
}

void test_1721()
{
	ListNode* head = new ListNode(1);
	ListNode* no2 = new ListNode(2);
	ListNode* no3 = new ListNode(3);
	ListNode* no4 = new ListNode(4);
	ListNode* no5 = new ListNode(5);
	head->next = no2;
	no2->next = no3;
	no3->next = no4;
	no4->next = no5;
	auto res = swapNodes(head, 2);
	while (res)
	{
		cout << res->val << endl;
		res = res->next;
	}
}
