#include <bits/stdc++.h>
using namespace std;

/**
 * Definition for a binary tree node.
 */
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

/**
 * 这题考察的是DFS：后序遍历的DFS
 * 题解思路：从下到上的DFS，从叶子结点开始，统计每个节点当前左右两个子树之和，并且判断子树之和是否等于当前节点的值
 */
class Solution
{
public:
    int ans = 0;

    int averageOfSubtree(TreeNode *root)
    {
        if (!root)
        {
            return 0;
        }
        getSubTreeSum(root);
        return ans;
    }

    pair<int, int> getSubTreeSum(TreeNode *root)
    {
        if (!root)
        {
            return {0, 0};
        }
        pair leftPair = getSubTreeSum(root->left);
        pair rightPair = getSubTreeSum(root->right);
        int cnt = leftPair.first + rightPair.first + 1;
        int sum = leftPair.second + rightPair.second + root->val;
        if (sum / cnt == root->val)
        {
            ans++;
        }
        return {cnt, sum};
    }
};

int main()
{
    Solution solution;

    TreeNode *root = nullptr;
    int ans = solution.averageOfSubtree(root);
    cout << ans << endl;

    return 0;
}