#include <bits/stdc++.h>
#include <iostream>
#include <deque>
using namespace std;

int main()
{
    deque<int> dq;
    
    // 头部和尾部操作
    dq.push_back(2);
    dq.push_back(3);
    dq.push_front(1);
    dq.push_front(0);
    // 此时：0 1 2 3

    // 头尾元素
    // 输出：0
    cout << dq.front() << endl;
    // 输出：3
    cout << dq.back() << endl;

    // 支持下标访问
    // 输出：1
    cout << dq[1] << endl;

    // 删除头尾
    dq.pop_front();
    dq.pop_back();
    // 此时：1 2

    // 大小
    // 输出：2
    cout << dq.size() << endl;

    // 遍历
    // 输出：1 2
    for (int x : dq) {
        cout << x << " ";
    }
    cout << endl;

    cout << dq.empty() << endl;

    return 0;
}