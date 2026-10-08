#include <vector>
#include <bits/stdc++.h>

using namespace std;

class Solution
{
public:
    int reflash(const vector<int> &locs, int num)
    {
        int ans = 0;
        int cur = 0;
        for (int i = 0; i < locs.size(); i++)
        {
            if (locs[i] != 0)
            {
                cur++;
                ans = max(ans, cur);
            }
            else
            {
                cur = 0;
            }
        }
        return ans;
    }

    int GetMaxLocDensity(const vector<int> &locs, int num)
    {
        // 题目分两步：
        // 1、更新num，num只会缩小
        num = min(reflash(locs, num), num);

        // 2、求最大值
        int zeroNum = 0;
        int left = 0;
        int right = 0;
        int curSum = 0;
        int ans = 0;
        while (right < locs.size())
        {
            curSum += locs[right];
            if (locs[right] == 0)
            {
                zeroNum++;
            }
            right++;
            if (right - left > num)
            {
                curSum -= locs[left];
                if (locs[left] == 0)
                {
                    zeroNum--;
                }
                left++;
            }
            if (right - left == num && zeroNum == 0)
            {
                ans = max(ans, curSum);
            }
        }
        return ans;
    }
};