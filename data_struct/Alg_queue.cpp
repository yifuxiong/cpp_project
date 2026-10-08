#include <bits/stdc++.h>
#include <iostream>
#include <queue>
using namespace std;

/**
 * 队列是先进先出（FIFO）的数据结构，BFS（广度优先搜索）中必用。
 */
int main()
{
    queue<int> q;
    q.push(10);
    q.push(20);
    q.push(30);

    // 队头元素
    // 输出：10
    cout << q.front() << endl;

    // 队尾元素
    // 输出：30
    cout << q.back() << endl;

    // 出队（删除队头）
    q.pop();

    // 新的队头
    // 输出：20
    cout << q.front() << endl;

    // 大小
    // 输出：2
    cout << q.size() << endl;

    // 判空
    // 输出：0（不为空）
    cout << q.empty() << endl;

    return 0;
}

// 注意：queue 的 pop() 没有返回值，如果想取出队头元素，需要先 front() 再 pop()