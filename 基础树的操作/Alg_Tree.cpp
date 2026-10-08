// cpp中，二叉树的三种深度优先遍历，先给节点定义和递归版（最简），再附迭代版（显式栈）。

/**
 * 节点定义
 */
#include <iostream>
#include <stack>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

/**
 * 递归版（简洁、易记）
 */
// 前序：根 → 左 → 右
void preorder(TreeNode *root)
{
    if (!root)
        return;
    std::cout << root->val << " ";
    preorder(root->left);
    preorder(root->right);
}

// 中序：左 → 根 → 右
void inorder(TreeNode *root)
{
    if (!root)
        return;
    inorder(root->left);
    std::cout << root->val << " ";
    inorder(root->right);
}

// 后序：左 → 右 → 根
void postorder(TreeNode *root)
{
    if (!root)
        return;
    postorder(root->left);
    postorder(root->right);
    std::cout << root->val << " ";
}

/**
 * 迭代版（显式栈，面试常考）
 */
// 前序：入栈时输出
void preorderIter(TreeNode *root)
{
    if (!root)
        return;
    std::stack<TreeNode *> st;
    st.push(root);
    while (!st.empty())
    {
        TreeNode *cur = st.top();
        st.pop();
        std::cout << cur->val << " ";
        if (cur->right)
            st.push(cur->right); // 先右后左，保证左先出
        if (cur->left)
            st.push(cur->left);
    }
}

// 中序：一路向左，左尽则出栈转右
void inorderIter(TreeNode *root)
{
    std::stack<TreeNode *> st;
    TreeNode *cur = root;
    while (cur || !st.empty())
    {
        while (cur)
        { // 先压入所有左子树
            st.push(cur);
            cur = cur->left;
        }
        cur = st.top();
        st.pop();
        std::cout << cur->val << " ";
        cur = cur->right; // 转向右子树
    }
}

// 后序：双栈法 —— 前序变体再逆序
// 用"根→右→左"遍历，结果倒序即"左→右→根"
void postorderIter(TreeNode *root)
{
    if (!root)
        return;
    std::stack<TreeNode *> st, out;
    st.push(root);
    while (!st.empty())
    {
        TreeNode *cur = st.top();
        st.pop();
        out.push(cur); // 先收集"根右左"
        if (cur->left)
            st.push(cur->left);
        if (cur->right)
            st.push(cur->right);
    }
    while (!out.empty())
    { // 逆序输出 = 后序
        std::cout << out.top()->val << " ";
        out.pop();
    }
}

/**
 * 使用示例
 */
// 构建:      1
//          /   \
//         2     3
//        / \
//       4   5
int main()
{
    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);

    std::cout << "前序: ";
    preorder(root); // 1 2 4 5 3
    std::cout << "\n中序: ";
    inorder(root); // 4 2 5 1 3
    std::cout << "\n后序: ";
    postorder(root); // 4 5 2 3 1
    return 0;
}
