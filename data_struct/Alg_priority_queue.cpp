#include <bits/stdc++.h>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

void func1()
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
}

/**
 * lambda表达式
 *
 * lambda 在算法题中用得最多的场景就是 sort 的自定义比较和 priority_queue 的自定义比较器，把前面的例子掌握好就够用了
 */
void func2()
{
    // 小顶堆：传入 greater<int>
    priority_queue<int, vector<int>, greater<int>> minHeap;

    // 自定义比较：用 lambda
    // 注意 priority_queue 的比较逻辑和 sort 相反
    // sort 中 return a < b 是升序
    // priority_queue 中 return a < b 是大顶堆（和直觉相反！）
    auto cmp = [](pair<int, int> &a, pair<int, int> &b)
    {
        // first 小的优先级高 → 小顶堆
        return a.first > b.first;
    };

    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> pq(cmp);
}

/**
 * 多条件排序（first 相等，再比较 second）
 */
void func3()
{
    auto cmp = [](const pair<int, int> &a, const pair<int, int> &b)
    {
        if (a.first != b.first)
        {
            // first不等：a.first > b.first → first更小的优先级更高（小顶堆）
            return a.first > b.first;
        }
        else
        {
            // first相等：比较second，second小优先
            return a.second > b.second;
        }
    };

    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> pq(cmp);

    pq.push({2, 5});
    pq.push({1, 10});
    pq.push({1, 3});
    pq.push({3, 1});

    while (!pq.empty())
    {
        auto top = pq.top();
        pq.pop();
        cout << top.first << "," << top.second << endl;
    }
    // 输出顺序：
    // 1,3
    // 1,10
    // 2,5
    // 3,1
}

int main()
{
    func3();
    return 0;
}

// 小顶堆的声明 priority_queue<int, vector<int>, greater<int>> 比较长，但这是固定写法，记住就行。三个模板参数分别是：元素类型、底层容器、比较函数。