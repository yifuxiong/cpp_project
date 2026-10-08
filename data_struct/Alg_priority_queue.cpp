#include <bits/stdc++.h>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main()
{
    // 默认是大顶堆，堆顶最大
    priority_queue<int> maxHeap;
    maxHeap.push(30);
    maxHeap.push(10);
    maxHeap.push(20);

    // 输出：30（最大的）
    cout << maxHeap.top() << endl;

    // 弹出最大的
    maxHeap.pop();

    // 输出：20
    cout << maxHeap.top() << endl;

    // 小顶堆，堆顶最小
    priority_queue<int, vector<int>, greater<int>> minHeap;
    minHeap.push(30);
    minHeap.push(10);
    minHeap.push(20);

    // 输出：10（最小的）
    cout << minHeap.top() << endl;
    minHeap.pop();

    // 输出：20
    cout << minHeap.top() << endl;

    // 大小和判空
    // 输出：2
    cout << minHeap.size() << endl;

    // 输出：0（不为空）
    cout << minHeap.empty() << endl;

    return 0;
}

// 小顶堆的声明 priority_queue<int, vector<int>, greater<int>> 比较长，但这是固定写法，记住就行。三个模板参数分别是：元素类型、底层容器、比较函数。