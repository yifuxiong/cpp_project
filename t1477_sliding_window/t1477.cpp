#include <bits/stdc++.h>
using namespace std;

/**
 * 示例 1：
 * 输入：arr = [3,2,2,4,3], target = 3
 * 输出：2
 * 解释：只有两个子数组和为 3 （[3] 和 [3]）。它们的长度和为 2 。
 */
class Solution
{
public:
    int minSumOfLengths(vector<int> &arr, int target)
    {
        int n = arr.size();
        int ans = n + 1;
        int sum = 0;
        // 用一个数组来记录遍历到第i个数时，前i个数的和为target的子数组的长度
        vector<int> dp(n + 1, n);
        for (int left = 0, right = 0; right < n; right++)
        {
            sum += arr[right];
            while (sum > target)
            {
                sum -= arr[left++];
            }
            dp[right + 1] = dp[right];
            if (sum == target)
            {
                ans = min(ans, right - left + 1 + dp[left]);
                // 更新遍历到后一个数时，前right个数的和为target的子数组的最小长度
                dp[right + 1] = min(dp[right], right - left + 1);
            }
        }
        return ans == n + 1 ? -1 : ans;
    }
};

int main()
{
    Solution solution;
    vector<int> arr = {3, 2, 2, 4, 3};
    int ans = solution.minSumOfLengths(arr, 3);
    cout << ans << endl;
    return 0;
}