/**
 * 第3题：树的上下及兄弟节点的遍历（这题原题没有找到，所以放了一道类似的题目）
 * 
要点：
- 用 unordered_map<int,int> 做“节点值 -> 下标”映射，节点用下标表示父子关系，避免 Java 里直接存对象引用。
- downDfs 改状态并向子孙扩散；
    upDfs 由子节点状态推导父节点（全相同则继承，否则为 0 半选），逐层向上。
- 与 Java 版有一处差异：Java 的 upDfs 在叶子节点处 return，导致叶子节点的操作不会向上传递；
    C++ 版去掉了该提前返回，严格按题目“状态逐层传递”的规则处理，样例结果不变
 */

#include <bits/stdc++.h>
using namespace std;

struct NTreeNode {
    int val;
    int statu = -1; // -1 未选, 0 半选, 1 全选
    int parent = -1; // 这个存放的是父节点的索引，在 unordered_map<int, int> id 中的索引
    vector<int> children; // 子节点列表
};

class Solution {
public:
    // <节点值, 下标>
    unordered_map<int, int> id;
    // 这个vector包含所有节点信息
    // 为了快速取到这个节点，按照1,2,3的顺序，给vector中所有节点都排了一个索引
    // 于是，上面的这个 unordered_map<int, int> id 就完成了"节点值"到"下标索引"的映射，快速找到当前节点的下标
    vector<NTreeNode> nodes;

    // 根据节点值拿到对应的节点索引（后面再根据这个索引在 vector<NTreeNode> nodes 取到对应的节点信息）
    int getNode(int val) {
        auto it = id.find(val);
        if (it != id.end()) {
            return it->second;
        }
        // 否则创建一个新的节点
        nodes.push_back(NTreeNode{val, -1, -1, {}});
        // 然后把值和索引做一个映射，加入到 unordered_map<int, int> id 中
        int idx = (int)nodes.size() - 1;
        id[val] = idx;
        // 最后返回这个索引
        return idx;
    }

    // 向下递归：把 u 及其所有子孙节点置为 newStatu
    void downDfs(int u, int newStatu) {
        if (u == -1) return;
        nodes[u].statu = newStatu;
        for (int v : nodes[u].children) downDfs(v, newStatu);
    }

    // 向上递归：由子节点状态推导父节点状态，直到根节点
    void upDfs(int u) {
        while (u != -1) {
            // 如果子节点列表不为空
            if (!nodes[u].children.empty()) {
                int firstStatu = nodes[nodes[u].children[0]].statu;
                bool isSameStatu = true;
                for (int v : nodes[u].children) {
                    if (nodes[v].statu != firstStatu) {
                        isSameStatu = false;
                        break;
                    }
                }
                // 子节点状态全相同则继承该状态，否则为半选
                nodes[u].statu = isSameStatu ? firstStatu : 0;
            }
            u = nodes[u].parent;
        }
    }

    // vector<vector<int>> &dirTree，对应的父节点和子节点的值
    // vector<int> &operations，对每个节点的状态操作
    int selectNodes(vector<vector<int>> &dirTree, vector<int> &operations) {
        for (auto &pair : dirTree) {
            int parentVal = pair[0];
            int curVal = pair[1];
            if (parentVal == -1)
                continue; // 根节点，虚父节点 -1

            // 节点值对应的索引，待会用于 vector<NTreeNode> nodes 中查找
            int cur = getNode(curVal);
            int par = getNode(parentVal);
            nodes[cur].parent = par;
            nodes[par].children.push_back(cur);
        }

        for (int op : operations) {
            int u = id[op];
            // -1 -> 1, 0 -> 1, 1 -> -1
            int nextStatu = nodes[u].statu < 1 ? 1 : -1;
            downDfs(u, nextStatu);
            upDfs(u);
        }

        int count = 0;
        for (auto &nd : nodes) {
            if (nd.statu == -1)
                count++;
        }
        return count;
    }
};

int main() {
    int n;
    if (!(cin >> n)) return 0;
    vector<vector<int>> dirTree(n, vector<int>(2));
    for (int i = 0; i < n; i++) cin >> dirTree[i][0] >> dirTree[i][1];

    int m;
    cin >> m;
    vector<int> operations(m);
    for (int i = 0; i < m; i++) cin >> operations[i];

    Solution solut;
    cout << solut.selectNodes(dirTree, operations) << endl;
    return 0;
}
