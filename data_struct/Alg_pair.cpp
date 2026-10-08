#include <bits/stdc++.h>
#include <iostream>
#include <utility>
#include <unordered_map>
using namespace std;

// pair 把两个值打包成一对，在算法题中经常用来存储坐标、键值对等。
void func1()
{
    // 创建 pair
    pair<string, int> p1 = make_pair("apple", 3);
    pair<string, int> p2 = {"banana", 5}; // c++11 简写

    // 访问两个元素
    // 输出：apple
    cout << p1.first << endl;
    // 输出：3
    cout << p1.second << endl;

    // 修改
    p1.second = 10;
    // 输出：10
    cout << p1.second << endl;

    // pair 可以直接比较（先比 first，再比 second）
    pair<int, int> a = {1, 3};
    pair<int, int> b = {1, 5};

    // 输出：1（a < b，因为 first 相同，3 < 5）
    cout << (a < b) << endl;
}

// 函数返回 pair
pair<int, int> divide(int a, int b)
{
    return {a / b, a % b};
}

/**
 * 结构化绑定 auto [k, v]
 * C++17 引入了结构化绑定，可以把 pair（以及其他结构）的成员直接拆开到独立变量中。遍历 map 的时候特别好用
 */
void func2()
{
    unordered_map<string, int> map;
    map["apple"] = 3;
    map["banana"] = 5;
    map["cherry"] = 2;

    // 遍历 map 时，用结构化绑定拆出 key 和 value
    for (auto& [key, value] : map) {
        cout << key << " -> " << value << endl;
    }

    // 接收函数返回的 pair
    auto [quotient, remainder] = divide(10, 3);
    // 输出：商=3，余=1
    cout << "商=" << quotient << "，余=" << remainder << endl;
}

int main()
{
    // func1();
    func2();

    return 0;
}