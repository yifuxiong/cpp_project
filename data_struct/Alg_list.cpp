#include <bits/stdc++.h>
#include <iostream>
#include <list>
using namespace std;

/**
 * list 是双向链表，在任意位置插入和删除都很快，但不支持下标随机访问
 *
 * list 没有 [] 运算符，不能像 vector 那样通过下标访问，只能通过迭代器遍历。这是链表的天然限制
 */
void func1()
{
    list<int> lst;

    // 头部和尾部添加：左头右尾
    lst.push_back(2);
    lst.push_back(3);
    lst.push_front(1);
    lst.push_front(0);
    // 此时：0 1 2 3

    // 这样也可以
    for (auto it = lst.begin(); it != lst.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;

    // 头尾元素
    // 输出：0
    cout << lst.front() << endl;
    // 输出：3
    cout << lst.back() << endl;

    // 删除头尾
    lst.pop_front();
    lst.pop_back();
    // 此时：1 2

    // 在中间插入：先用 advance 移动迭代器
    auto it = lst.begin();
    advance(it, 1); // 移动到索引 1 的位置
    lst.insert(it, 99);
    // 此时：1 99 2

    // 删除中间元素
    it = lst.begin();
    advance(it, 1);
    lst.erase(it);
    // 此时：1 2

    // 遍历
    // 输出：1 2
    for (int x : lst)
    {
        cout << x << " ";
    }
    cout << endl;

    // 大小
    // 输出：2
    cout << lst.size() << endl;
}

int main()
{
    func1();
    return 0;
}