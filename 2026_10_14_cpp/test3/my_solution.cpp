/**
 * 跟着cpp的代码思路自己写一遍
 */

#include <bits/stdc++.h>
using namespace std;

struct NTreeNode
{
    int val;
    int statu = -1;
    int parent = -1;      // 存的id
    vector<int> children; // 这里面存的也是id
};

class Solution
{
public:
    unordered_map<int, int> id;
    vector<NTreeNode> nodes;

    // u是节点id
    void downDfs(int u, int newStatu)
    {
        if (u == -1)
        {
            return;
        }
        nodes[u].statu = newStatu;
        for (int v : nodes[u].children)
        {
            downDfs(v, newStatu);
        }
    }

    // u是节点id
    void upDfs(int u)
    {
        while (u != -1)
        {
            // 如果子节点列表不为空
            if (!nodes[u].children.empty())
            {
                // 先取到第一个儿子节点的状态
                int firstChildStatu = nodes[nodes[u].children[0]].statu;
                bool isSameStatu = true;
                for (int v : nodes[u].children)
                {
                    if (nodes[v].statu != firstChildStatu)
                    {
                        isSameStatu = false;
                        break;
                    }
                }
                // 子节点状态全部相同，则继承该状态，否则设置为半选状态
                nodes[u].statu = isSameStatu ? firstChildStatu : 0;
            }
            // 如果子节点列表为空，因此该节点状态不改变，继续往上遍历更新父节点状态
            u = nodes[u].parent;
        }
        // 如果是根节点，就直接退出
    }

    // 根据value取到对应的idx
    int getNodeIdx(int value)
    {
        auto iter = id.find(value);
        if (iter != id.end())
        {
            return iter->second;
        }
        // 否则创建一个新的节点
        nodes.push_back({value, -1, -1, {}});
        int idx = (int)nodes.size() - 1;
        id[value] = idx;
        return idx;
    }

    // vector<vector<int>> &dirTree，对应的父节点和子节点的值
    // vector<int> &operations，对每个节点的状态操作
    int selectNodes(vector<vector<int>> &dirTree, vector<int> &operations)
    {
        // 先更新 nodes
        for (auto &pair : dirTree)
        {
            int parentVal = pair[0];
            int curVal = pair[1];
            if (parentVal == -1)
            {
                // 根节点
                continue;
            }
            int curIdx = getNodeIdx(curVal);
            int parentIdx = getNodeIdx(parentVal);
            nodes[curIdx].parent = parentIdx;
            nodes[parentIdx].children.push_back(curIdx);
        }

        // 更新节点状态
        for (int op : operations)
        {
            int u = id[op];
            int nextStatu = nodes[u].statu < 1 ? 1 : -1;
            downDfs(u, nextStatu);
            upDfs(u);
        }

        // 返回未选中的节点数量
        int count = 0;
        for (auto &nd : nodes)
        {
            if (nd.statu == -1)
            {
                count++;
            }
        }
        return count;
    }
};