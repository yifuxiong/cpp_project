#include <bits/stdc++.h>
#include <iostream>
#include <unordered_map>
using namespace std;

void func1()
{
    unordered_map<string, int> map;
    // 添加键值对（直接用 [] 赋值）
    map["apple"] = 3;
    map["banana"] = 5;
    map["cherry"] = 2;

    // 通过 key 获取 value
    // 输出：3
    cout << map["apple"] << endl;

    // 判断 key 是否存在（C++20，本地编译需加 -std=c++20）
    // 如果编译器不支持，可以用 map.count("banana") 代替
    cout << map.count("banana") << endl; // 输出：1
    cout << map.count("grape") << endl;  // 输出：0

    // 删除
    map.erase("cherry");

    // 大小
    // 输出：2
    cout << map.size() << endl;

    // 遍历（顺序不保证）
    for (auto &[key, value] : map)
    {
        cout << key << " -> " << value << endl;
    }
}

void func2()
{
    // 统计每个字符出现的次数
    unordered_map<char, int> count;
    string s = "hello";
    for (char c : s)
    {
        count[c]++;
    }
}

/**
 * 特别注意：访问不存在的键会自动插入
 *
 * 这是 C++ 新手最容易踩的坑之一。
 * 用 [] 访问一个不存在的 key，unordered_map 会自动插入这个 key，value 为默认值（int 类型默认为 0）
 */
void func3()
{
    unordered_map<string, int> map;
    map["apple"] = 3;

    // 此时只有 1 个元素
    // 输出：1
    cout << map.size() << endl;

    // 访问不存在的 key "grape"
    // 这会自动插入 {"grape": 0}！
    cout << map["grape"] << endl;

    // 现在变成了 2 个元素！
    // 输出：2
    cout << map.size() << endl;

    // 所以，判断 key 是否存在一定要用 contains，不要用 []
    // 判断 key 是否存在（C++20，本地编译需加 -std=c++20），如果编译器不支持，可以用 map.count("apple") 代替
    if (map.count("orange"))
    {
        cout << map["orange"] << endl;
    }
    else
    {
        // 输出 origin not found
        cout << "orange not found" << endl;
    }
}

int main()
{
    // func1();
    // func2();
    func3();

    return 0;
}