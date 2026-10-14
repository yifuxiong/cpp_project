#include <bits/stdc++.h>
#include <iostream>
#include <climits>
using namespace std;

int main() {
    // int 范围：大约 -21亿 ~ 21亿
    // 输出：2147483647
    cout << INT_MAX << endl;
    // 输出：-2147483648
    cout << INT_MIN << endl;

    // long long 范围：大约 -9.2 * 10^18 ~ 9.2 * 10^18
    // 输出：9223372036854775807
    cout << LLONG_MAX << endl;

    // 溢出演示：MAX + 1 变成 MIN
    int x = INT_MAX;
    // 输出：-2147483648
    cout << x + 1 << endl;

    // 算法题中常见用法：用 INT_MAX 表示"无穷大"
    int minVal = INT_MAX;
    int nums[] = {5, 2, 8, 1, 9};
    for (int n : nums) {
        minVal = min(n, minVal);
    }
    cout << minVal << endl;

    return 0;
}