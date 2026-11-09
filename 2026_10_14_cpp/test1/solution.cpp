/**
 * 第1题：面对面建群

题目描述：有一群人，每个人3个信息：(feature, x, y)，表示各自的特征（feature）值和坐标（x, y）。
现在要求大家面对面建群，按输入顺序依次考虑每一个人，建群和加群规则为：
（1）如果有多个（>=1）群可以加入，优先加入最早建立的群。每个人可以加入一个已存在的群的条件为：
    自己和群主的feature数值相等，并且自己和群主在同一个九宫格里。即：两个人的x坐标和y坐标差值都不大于1.
（2）如果当前这个人不能加入所有已存在的群，则新建一个新群，当前这个人成为群主。

请依次顺序执行，让每个人都加群。输出所有人都加了群之后每个人的人数，人数按降序排序。

样例：
输入：[[1, 1, 1], [1, 2, 3], [1, 1, 2]]
输出： [2, 1]

样例解释：
首先第一个人建自己的群，第二个人虽然feature和第一个人相同但是超出了九宫格的范围所以建第2个群，
第三个人同时满足加现有的两个群的条件但是优先加入序号小的群，所以最终是1、3两个人一个群，第2个人一个人一个群。

数据范围：
人数 <= 1000，1 <= feature <= 100，0 <= x,y <= 100
（可能有误，但是总之很小，都是不超过1000的）
 */

/**
 * 这里用agent帮忙生成了一份cpp版的代码
 * 
 * 样例：
 * 
 * 坐标示意（x 向右，y 向上）
 y
 4
 3 |        [P2](2,3)   ← 建立 G2（与 P1 的 y 差 2，超出九宫格）
 2 |     [P3](1,2)      ← 同时在 P1、P2 的九宫格内，加入更早的 G1
 1 |  [P1](1,1)         ← 建立 G1（群主）
 0 +------------------------ x
     0   1   2   3   4

P1 的九宫格(x:0~2, y:0~2)      P2 的九宫格(x:1~3, y:2~4)
┌───────────────┐              ┌───────────────┐
│ .   .   .     │  y=2         │ .   .   .     │
│ .  [P3] .     │              │ .  [P3] .     │
│ .   .  [P1]   │  y=1         │ .   .   .     │
└───────────────┘              └───────────────┘
        ↑ P3 命中，且 G1 更早建立 → 加入 G1
        
最终：G1 = {P1, P3}，G2 = {P2} → 各群人数 [2, 1]
按顺序：P1 建群 → P2 因超出九宫格建群 → P3 同时满足两群，优先加入最早的 G1。
 */

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    struct Group
    {
        // 这个群中心点的位置：行
        int x;
        // 这个群中心点的位置：列
        int y;
        // 群标识码：表示这个群中成员的爱好 
        int id;
    };

    vector<int> resolve(const vector<tuple<int, int, int>> &members)
    {
        unordered_map<int, vector<Group>> groupsByFeature;
        // 成员数
        vector<int> counts;

        for (const auto &m : members)
        {
            auto [feature, x, y] = m;
            auto &groups = groupsByFeature[feature];
            bool joined = false;

            for (const auto &g : groups)
            {
                if (abs(x - g.x) <= 1 && abs(y - g.y) <= 1)
                {
                    // 新成员在当前这个group的覆盖范围内，那就直接加入，该群的成员数+1
                    ++counts[g.id];
                    joined = true;
                    break;
                }
            }

            if (!joined)
            {
                // 新建一个群
                int id = static_cast<int>(counts.size());
                groups.push_back({x, y, id});
                counts.push_back(1);
            }
        }

        // 逆序输出
        sort(counts.begin(), counts.end(), greater<int>());
        return counts;
    }

    int main()
    {
        int n;
        if (!(cin >> n))
            return 0;

        vector<tuple<int, int, int>> members(n);
        for (auto &m : members)
            cin >> get<0>(m) >> get<1>(m) >> get<2>(m);

        vector<int> result = resolve(members);
        for (size_t i = 0; i < result.size(); ++i)
        {
            if (i)
                cout << ' ';
            cout << result[i];
        }
        cout << '\n';
        return 0;
    }
};