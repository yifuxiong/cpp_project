#include <bits/stdc++.h>
using namespace std;

/**
 * 题目二：最大位置密度
题目背景
给定一条线路上各个位置的评估值，用整数数组 locs 表示。locs[i] > 0 表示该位置有效，数值为其密度；locs[i] == 0 表示该位置不可用。现在要求从中选取连续 num 个位置，使得所选位置的值之和最大。注意：所选的连续区间内不允许包含任何 0。

接口定义
int GetMaxLocDensity(const vector<int>& locs, int num);

如果 num的值大于数组中最长连续非零段的长度， 则修正num为数组中最长连续非零段的长度
 */

int GetMaxLocDensity(const vector<int> &locs, int num)
{
    // 记录数组中最长连续非零段的长度
    int maxNonZeroLength = 0;
    // 记录前缀和
    vector<int> preSum = {};
    // 值为0的位置索引
    vector<int> zeroIndex = {};

    /**
     * 遍历第一遍：
     * 1、判断数组中是否存在长度为num的非零段子数组
     * 2、记录最长连续非零段的长度
     * 3、计算前缀和
     * 4、记录当前值为0的位置索引
     */
    int left = 0, right = 0;
    int length = locs.size();
    while (right < length) {
        if (right == 0) {
            preSum.push_back(locs[right]);
        } else {
            preSum.push_back(preSum[right - 1] + locs[right]);
        }

        if (locs[right] == 0) {
            zeroIndex.push_back(right);
            maxNonZeroLength = max(maxNonZeroLength, right - left);
            left = right + 1;
            right = left;
        } else {
            right++;
        }
    }
    // 更新num
    if (num > maxNonZeroLength) {
        num = maxNonZeroLength;
    }

    // 遍历第2遍，在preSum中根据值为0的索引去找
    int maxRes = 0;
    int pre = 0, post = 0;
    for (int i = 0; i < zeroIndex.size(); i++) {
        pre = post;
        post = zeroIndex[i];
        if (post - pre == num) {
            maxRes = max(maxRes, preSum[post] - preSum[pre]);
        }
    }
    return maxRes;
}