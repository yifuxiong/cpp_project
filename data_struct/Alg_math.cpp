#include <bits/stdc++.h>
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

/**
 * C++ 的数学函数在 <cmath> 头文件中。另外 max、min、swap 这些是 C++ 内置的，在 <algorithm> 中，不需要自己写
 */
int main()
{
    // max 和 min（C++ 内置，不需要自己写！）
    cout << min(10, 20) << endl;
    cout << max(10, 20) << endl;

    // swap 也是内置的
    int a = 1, b = 2;
    swap(a, b);
    cout << a << " " << b << endl;

    // 绝对值：整数用 abs，浮点数用 fabs
    cout << abs(-5) << endl;
    cout << fabs(-3.14) << endl;

    // 幂运算
    cout << pow(2, 3) << endl;

    // 开方
    cout << sqrt(9) << endl;

    // 取整
    // 输出：3（向下取整）
    cout << (int)floor(3.7) << endl;
    // 输出：4（向上取整）
    cout << (int)ceil(3.2) << endl;

    return 0;
}

// 注意：pow 返回 double 类型，在需要精确整数结果的场景下（比如 pow(2, 10) 期望得到 1024），由于浮点精度问题可能得到 1023.999...。如果需要整数幂运算，建议自己写循环或者用位运算（1 << 10）