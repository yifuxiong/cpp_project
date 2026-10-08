#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// 全排列问题，有重复数字
/**
 * 给定一个可【包含重复】数字的序列，返回所有不重复的全排列。
 * 输入: [1,2,2]
 * 输出:
 * [
 *   [1,2,2],
 *   [2,1,2],
 *   [2,2,1]
 * ]
 */
class PermutationsII
{
public:
    std::vector<std::vector<int>> permuteII(std::vector<int> &nums)
    {
        std::sort(nums.begin(), nums.end());
        std::vector<std::vector<int>> ans;
        std::vector<bool> used(nums.size(), false);
        std::vector<int> tmp;
        backTrace(nums, used, ans, tmp);
        return ans;
    }

private:
    void backTrace(const std::vector<int> &nums, std::vector<bool> &used,
                   std::vector<std::vector<int>> &ans, std::vector<int> &tmp)
    {
        if (tmp.size() == nums.size())
        {
            ans.push_back(tmp);
            return;
        }
        for (size_t i = 0; i < nums.size(); i++)
        {
            if (!used[i])
            {
                if (i > 0 && nums[i] == nums[i - 1] && used[i - 1])
                {
                    continue;
                }
                tmp.push_back(nums[i]);
                used[i] = true;
                backTrace(nums, used, ans, tmp);
                used[i] = false;
                tmp.pop_back();
            }
        }
    }
};

int main()
{
    std::vector<int> nums = {2, 1, 2};

    PermutationsII pII;
    std::vector<std::vector<int>> result = pII.permuteII(nums);
    std::cout << "[";
    for (size_t i = 0; i < result.size(); i++)
    {
        std::cout << "[";
        for (size_t j = 0; j < result[i].size(); j++)
        {
            std::cout << result[i][j];
            if (j + 1 < result[i].size())
                std::cout << ", ";
        }
        std::cout << "]";
        if (i + 1 < result.size())
            std::cout << ", ";
    }
    std::cout << "]" << std::endl;
    return 0;
}