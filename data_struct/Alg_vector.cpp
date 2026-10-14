#include <bits/stdc++.h>
#include <vector>
using namespace std;

void func1()
{
    // 空 vector
    vector<int> v1;

    // 指定大小，默认值为 0
    vector<int> v2(5); // {0, 0, 0, 0, 0}

    // 指定大小和初始值
    vector<int> v3(5, -1); // {-1, -1, -1, -1, -1}

    // 初始化列表
    vector<int> v4 = {1, 2, 3, 4, 5};

    // 二维 vector：3 行 4 列，初始值为 0
    vector<vector<int>> grid(3, vector<int>(4, 0));
}

void func2()
{
    vector<int> nums = {10, 20, 30};

    // 尾部添加元素
    nums.push_back(40);
    nums.push_back(50);

    // 大小
    // 输出：5
    cout << nums.size() << endl;

    // 判空
    // 输出：0（不为空）
    cout << nums.empty() << endl;

    // 通过下标访问
    // 输出：10
    cout << nums[0] << endl;

    // 最后一个元素
    // 输出：50
    cout << nums.back() << endl;

    // 删除最后一个元素
    nums.pop_back();
    // 输出：40
    cout << nums.back() << endl;

    // 在索引 1 处插入 99
    nums.insert(nums.begin() + 1, 99);

    // 删除索引 2 处的元素
    nums.erase(nums.begin() + 2);

    /**
     * insert 和 erase 的参数都是迭代器（可以理解为指向容器中某个元素的指针），不是索引。nums.begin() 指向第一个元素，nums.begin() + i 就是索引 i 的位置。这两个操作需要搬移元素，效率不高，尽量少用
     */

    // 交换两个 vector 的内容
    vector<int> other = {100, 200};
    nums.swap(other);
    // 此时 nums = {100, 200}，other = {10, 99, 30, 40}

    // 用下标遍历
    // 输出：100 200
    for (int i = 0; i < nums.size(); i++)
    {
        cout << nums[i] << " ";
    }
    cout << endl;

    // 用 range-based for 遍历
    // 输出：10 99 30 40
    for (int x : other)
    {
        cout << x << " ";
    }
    cout << endl;
}

/**
 * 二维 vector 在表示矩阵、网格时非常常用
 */
void func3()
{
    // 创建 3 行 4 列的二维 vector，初始值为 0
    int rows = 3, cols = 4;
    vector<vector<int>> grid(rows, vector<int>(cols, 0));

    // 赋值
    grid[0][0] = 1;
    grid[1][2] = 5;
    grid[2][3] = 9;

    // 行数和列数
    // 输出：3 行 4 列
    cout << grid.size() << " 行 " << grid[0].size() << " 列 " << endl;

    // 遍历
    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[0].size(); j++)
        {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

// sort
void func4()
{
    vector<int> nums = {5, 2, 4, 3, 1};
    sort(nums.begin(), nums.end());
    for (int num : nums)
    {
        cout << num << " ";
    }
    cout << endl;

    // 降序：传入自定义比较函数（lambda 表达式）
    sort(nums.begin(), nums.end(), [](int a, int b)
         { return a > b; });
    for (int num : nums)
    {
        cout << num << " ";
    }
    cout << endl;
}

/**
 * 按照字符串大小排序
 *
 * 如果是纯字符串，可以直接重载运算符，直接用 >, <, ==
 * 但是如果是数字型字符串，用重载的运算符直接比价可能有坑，比如 "9" > "10"，因为 "9" > "1"，要用 `stoi/stoll` 转数字再比，当然也可以用string::compare()来比较
 */
void func5()
{
    vector<string> words = {"banana", "apple", "kiwi", "cherry"};

    sort(words.begin(), words.end(), [](string &a, string &b)
         { return a > b; });

    for (string &word : words)
    {
        cout << word << " ";
    }
    cout << endl;
}

/**
 * 多级排序
 */
struct Student
{
    string name;
    int score;
};

void func6()
{
    vector<Student> students = {
        {"Charlie", 85},
        {"Alice", 92},
        {"Bob", 85},
        {"Amy", 85}};

    sort(students.begin(), students.end(), [](Student &a, Student &b)
         {
        // 先按分数降序
        if (a.score != b.score) {
            return a.score > b.score;
        }
        return a.name < b.name; });

    for (Student &student : students)
    {
        cout << student.name << ": " << student.score << endl;
    }
    cout << endl;
}

int main()
{
    // func2();
    // func3();
    // func4();
    // func5();
    func6();
    return 0;
}