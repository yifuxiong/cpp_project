#include <bits/stdc++.h>
#include <iostream>
#include <map>
using namespace std;

/**
 * map 和 unordered_map 的 API 基本一样，区别是 map 的 key 是有序的（按照 key 的自然顺序排列），并且额外提供了 lower_bound 和 upper_bound 来利用有序性。
 *
 * map 的增删查改比 unordered_map 慢一些（底层是红黑树），但在需要有序性的场景下非常有用。
 */
int main()
{
    map<int, string> m;
    m[3] = "three";
    m[1] = "one";
    m[5] = "five";
    m[2] = "two";

    // 遍历是有序的（按 key 排序）
    // 输出：1->one 2->two 3->three 5->five
    for (auto &[key, value] : m)
    {
        cout << key << " -> " << value << " ";
    }
    cout << endl;

    // lower_bound：返回指向 >= 给定 key 的第一个元素的迭代器
    auto it = m.lower_bound(2);
    // 输出：2->two
    cout << it->first << "->" << it->second << endl;

    // upper_bound：返回指向 > 给定 key 的第一个元素的迭代器
    it = m.upper_bound(2);
    // 输出：3->three
    cout << it->first << "->" << it->second << endl;

    // 如果找不到，返回 end()
    it = m.lower_bound(100);
    if (it == m.end())
    {
        // 输出：not found
        cout << "not found" << endl;
    }

    return 0;
}

// 简单记：lower_bound(k) 找的是 >= k 的最小 key，upper_bound(k) 找的是 > k 的最小 key。
