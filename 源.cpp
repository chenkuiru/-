#include <stdio.h>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <map>
#include <math.h>
#include "binaryTree.h"
#include "LFUCache.h"
#include "slidingWindow.h"
#include "linkList.h"
#include "sort.h"
#include "dp.h"

using namespace std;


void rotate(vector<int>& nums, int k) {
    if (nums.size() == 0 || k == 0) return;
    int i = 0;
    int length = nums.size();
    vector<int> temp(nums);

    for (int i = 0; i < length - 1; i++)
    {
        int oldindex = i;
        int newindex = (oldindex + k > length) ? oldindex + k - length : oldindex + k;
        temp[newindex] = nums[oldindex];
    }

    for (int i = 0; i < temp.size(); i++)
    {
        nums[i] = temp[i];
    }
}

bool containsDuplicate(vector<int>& nums)
{
    vector<int> temp;
    bool iRet = false;
    for (int i = 0; i < nums.size(); i++)
    {
        vector<int>::iterator iter = std::find(temp.begin(), temp.end(), nums[i]);
        if (temp.size() == 0 || iter == temp.end())
        {
            temp.push_back(nums[i]);
        }
        else
        {
            iRet = true;
            break;
        }
    }

    return iRet;
}

bool containsDuplicate2(vector<int>& nums) {
    unordered_set<int> mset ;
    for (int x:nums) {
        if (mset.find(x)!=mset.end())
            return true;

        mset.insert(x);
    }
    return false;

    }

void rotate(vector<vector<int>>& matrix) {
    if (matrix.size() == 0) return;
    int n = matrix.size();
    for (int i = 0; i < n / 2; i++)
    {
        swap(matrix[i], matrix[n - 1 - i]);
    }

    for (int i = 0; i < n; i++)
    {
        int length = matrix[i].size();
        for (int j = i + 1; j < length; j++)
        {
            swap(matrix[i][j], matrix[j][i]);
        }
    }

}

int singleNumber(vector<int>& nums)
{
    
        int ret = 0;
        for (auto e : nums) ret ^= e;
        return ret;
    

}

vector<int> intersect(vector<int>& nums1, vector<int>& nums2)
{
    std::sort(nums1.begin(), nums1.end());
    std::sort(nums2.begin(), nums2.end());
    vector<int> res;
    int i = 0;
    int j = 0;
    while (i < nums1.size() && j < nums2.size())
    {
        if (nums1[i] == nums2[j])
        {
            res.push_back(nums1[i]);
            i++;
            j++;
        }
        else if (nums1[i]>nums2[j])
        {
            j++;
        }
        else
        {
            i++;
        }
    }
    return res;

}

vector<int> intersect2(vector<int>& nums1, vector<int>& nums2)
{
    vector<int> res;
    std::map<int, int> temp;
    for (int i = 0; i < nums1.size(); i++)
    {
        
        if(temp.find(nums1[i]) != temp.end())
        {
            temp.insert(make_pair(nums1[i], 1));
        }
        else
        {
            temp[nums1[i]]++;
        }
    }

    for (int i = 0; i < nums2.size(); i++)
    {
        if (temp[nums2[i]]>0)
        {
            res.push_back(nums2[i]);
            temp[nums2[i]]--;
        }
    }
    return res;

}

vector<int> plusOne(vector<int>& digits)
{
    vector<int> res;
    if (digits.size() == 0) return res;
    int num = 0;
    for (int i = 0; i < digits.size(); i++)
    {
        num = num + digits[i] * pow(10, digits.size() - 1 - i);
    }
    num++;
    int tmp = 0;
    if (num / (pow(10, digits.size() - 1)) == 10)
    {
        tmp = digits.size() + 1;
    }
    else
    {
        tmp = digits.size();
    }

    for (int i = tmp; i>0; i--)
    {
        int r = num / pow(10, i - 1);
        res.push_back(r);
        num = num % int(pow(10, i - 1));
    }
    return res;
}

vector<int> plusOne2(vector<int>& digits)
{
    int length = digits.size();
    if (length == 0) return digits;
    int count = 0;
    for(int i = length-1; i >= 0; i--)
    {
        if (digits[i] != 9)
        {
            digits[i]++;
            return digits;
        }
        else
        {
            count++;
            digits[i] = 0;
        }
        if(i==0)
            digits.insert(digits.begin(), 1);
    }
    return digits;
    /*if (count == length)
    {
        digits.insert(digits.begin(), 1);
        return digits;
    }*/
}

void moveZeroes(vector<int>& nums)
{
    int length = nums.size();
    if (length < 2) return;
    int left = 0;
    int right = 0;
    while (right < length && left<length)
    {
        if (nums[left] != 0)
        {
            left++;
            right++;
        }
        else
        {
            if (nums[right] != 0)
            {
                swap(nums[left], nums[right]);
                left++;
                right++;
            }
            else
            {
                right++;
            }
        }
        
    }
    /*for (int i = left; i < length - 1; i++)
    {
        nums[i] == 0;
    }*/
}

vector<int> twoSum(vector<int>& nums, int target)
{
    unordered_map<int, int> hashmap;
    for (int i = 0; i < nums.size(); i++)
    {
        auto iter = hashmap.find(target - nums[i]);
        if (iter != hashmap.end())
        {
            return { iter->second,i };
        }
        hashmap[nums[i]] = i;
    }
    return {};

}

bool isValidSudoku(vector<vector<char>>& board)
{
    vector<map<char, int>> row(9);
    vector<map<char, int>> column(9);
    vector<map<char, int>> box(9);

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            char c = board[i][j];
            if (c == '.')
                continue;
            if (row[i].find(c) != row[i].end())
            {
                return false;
            }
            else
            {
                row[i].insert(make_pair(c, 1));
            }

            if (column[j].find(c) != column[j].end())
            {
                return false;
            }
            else
            {
                column[j].insert(make_pair(c, 1));
            }

            if (box[(i / 3) * 3 + j / 3].find(c) != box[(i / 3) * 3 + j / 3].end())
            {
                return false;
            }
            else
            {
                box[(i / 3) * 3 + j / 3].insert(make_pair(c, 1));
            }
        }
    }
    return true;
}

int main()
{
   

    vector<int> nums{ 0,1,2,3,4,5 };
    TreeNode* root = sortedArrayToBST(nums);

    //vector<vector<int>> res = levelOrder(root);
    //vector<int> res = inorderTraversal(root);
    //vector<vector<int>> vec;
    /*vector<int> v1{ 1,2,3 };
    vector<int> v2{ 4,5,6 };
    vec.push_back(v1);
    vec.push_back(v2);*/
    //vec[1][1] = 0;
    //int num = vec[1][1];
    //int i = numTrees(3);
    //vector<vector<int>> tmp = zigzagLevelOrder(root);

    ///*vector<int> pre{ 3,9,20,15,7 };
    //vector<int> in{ 9,3,15,20,7 };
    //vector<int> post{ 9,15,7,20,3 };
    //TreeNode* root1 = backbuildTree(in, post);*/
    

    /*treenode* node3 = new treenode(3);
    treenode* node4 = new treenode(4);
    treenode* node6 = new treenode(6);
    treenode* node2 = new treenode(2,node3,node4);
    treenode* node5 = new treenode(5,nullptr,node6);
    treenode* node1 = new treenode(1,node2,node5);
    flatten(node1);*/
    
    test_1024();
    

    return 0;
}