#include <stdio.h>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <map>
#include <math.h>

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
    vector<char> v1{ '5','3','.','.','7','.','.','.','.' };
    vector<char> v2{ '5','.','.','1','9','5','.','.','.' };
    vector<char> v3{ '.','9','8','.','.','.','.','6','.' };
    vector<char> v4{ '8','.','.','.','6','.','.','.','3' };
    vector<char> v5{ '4','.','.','8','.','3','.','.','1' };
    vector<char> v6{ '7','.','.','.','2','.','.','.','6' };
    vector<char> v7{ '.','6','.','.','.','.','2','8','.' };
    vector<char> v8{ '.','.','.','4','1','9','.','.','5' };
    vector<char> v9{ '.','.','.','.','8','.','.','7','9' };
    vector<vector<char>> v;
    v.push_back(v1);
    v.push_back(v2);
    v.push_back(v3);
    v.push_back(v4);
    v.push_back(v5);
    v.push_back(v6);
    v.push_back(v7);
    v.push_back(v8);
    v.push_back(v9);


    bool res = isValidSudoku(v);
   



    return 0;
}