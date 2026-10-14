#include <bits/stdc++.h>
#include <iostream>
#include <bitset>
#include <string>
using namespace std;

int main() {
    int n = 42;

    // 十进制 -> 二进制：用 bitset
    // 输出：00101010
    cout << bitset<8>(n) << endl;

    // 转成字符串后去掉前导零
    string bin = bitset<32>(n).to_string();
    bin = bin.substr(bin.find('1'));
    // 输出：101010
    cout << bin << endl;

    // // 十进制 -> 八进制、十六进制：用流操纵符
    // // 输出：52
    // cout << oct << n << endl;
    // // 输出：2a
    // cout << hex << n << endl;
    // // 记得切回十进制，否则后续输出都是十六进制
    // cout << dec;

    // // 其他进制 -> 十进制：用 stoi(字符串, nullptr, 进制)
    // // 输出：42
    // cout << stoi("101010", nullptr, 2) << endl;
    // // 输出：42
    // cout << stoi("52", nullptr, 8) << endl;
    // // 输出：42
    // cout << stoi("2a", nullptr, 16) << endl;

    // // 实用技巧：统计二进制中 1 的个数
    // // __builtin_popcount 是 GCC/Clang 内置函数
    // // 输出：42 的二进制有 3 个 1
    // cout << n << " 的二进制有 " << __builtin_popcount(n) << " 个 1" << endl;

    return 0;
}