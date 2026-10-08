#include <bits/stdc++.h>
using namespace std;

int main()
{
    int matrix[3][4];
    // 初始化为0，函数原型：void * __cdecl memset(void *_Dst,int _Val,size_t _Size);
    memset(matrix, 0, sizeof(matrix));

    matrix[0][0] = 1;
    matrix[1][2] = 5;

    // 行数和列数
    int rows = sizeof(matrix) / sizeof(matrix[0]);
    int cols = sizeof(matrix[0]) / sizeof(matrix[0][0]);
    printf("%d 行 %d 列\n", rows, cols);

    // 也可以直接初始化
    int grid[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    return 0;
}