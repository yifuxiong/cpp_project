/**
 * 跟着cpp的代码思路自己写一遍
 */

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    // 新建一个Group结构体
    struct Group
    {
        // 该组的兴趣爱好分类id
        int categoryId;
        // 该组的坐标
        int x;
        int y;
    };

    // 按照逆序返回所有group的成员数
    vector<int> resolve(const vector<tuple<int, int, int>> &members)
    {
        // 待返回的结果
        vector<int> counts;
        //
        unordered_map<int, vector<Group>> groupByCategory;

        // 遍历每个成员，更新 groupByCategory 这个 map
        for (const auto &mem : members)
        {
            auto [categoryId, x, y] = mem;
            auto &groups = groupByCategory[categoryId];
            // 判断是否已经加群了
            bool joined = false;

            for (const auto &group : groups)
            {
                if (abs(group.x - x) <= 1 && abs(group.y - y) <= 1)
                {
                    // 在该群的覆盖范围内
                    counts[group.categoryId]++;
                    joined = true;
                    break;
                }
            }

            if (!joined)
            {
                // 这个兴趣爱好类型的 groups 里面再创建新一个群，把该成员加进去
                categoryId = static_cast<int>(counts.size() + 1);
                groups.push_back({categoryId, x, y});
                counts.push_back(1);
            }
        }

        // 最后逆序输出
        sort(counts.begin(), counts.end(), greater<int>());
        // sort(counts.begin(), counts.end(), [](int a, int b) {
        //     return a > b;
        // });
        return counts;
    }
};