#include <bits/stdc++.h>
#include <iostream>
#include <stack>
using namespace std;

int main()
{
    stack<int> stk;

    // 入栈
    stk.push(1);
    stk.push(2);
    stk.push(3);

    // 查看栈顶（不删除）
    // 输出：3
    cout << stk.top() << endl;

    // 出栈（删除栈顶）
    stk.pop();

    // 新的栈顶
    // 输出：2
    cout << stk.top() << endl;

    // 大小
    // 输出：2
    cout << stk.size() << endl;

    // 判空
    // 输出：0（不为空）
    cout << stk.empty() << endl;

    return 0;
}

// 和 queue 一样，stack 的 pop() 也没有返回值，想取栈顶元素要先 top() 再 pop()