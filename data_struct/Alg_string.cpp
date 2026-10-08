#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <string.h>
#include <cctype>
using namespace std;

/**
 * C语言中的string
 */
void func1()
{
    // 两种声明方式，效果一样
    // 编译器会自动在末尾加 \0
    char s1[] = "hello";
    char s2[] = {'h', 'e', 'l', 'l', 'o', '\0'};

    printf("s1: %s\n", s1);
    printf("s2: %s\n", s2);

    printf("s1.length is: %d\n", (int)strlen(s1));
    printf("s2.length is: %d\n", (int)strlen(s2));

    // 可以通过下标访问和修改单个字符
    s1[0] = 'H';
    // 输出：Hello
    printf("s1: %s\n", s1);

    for (int i = 0; i < (int)strlen(s1); i++)
    {
        printf("%c ", s1[i]);
    }
    printf("\n");
}

/**
 * 常用字符串函数，这些函数都在 <string.h> 中
 */
void func2()
{
    char s[] = "hello";

    // strcpy：复制字符串
    char dest[100];
    strcpy(dest, s);
    printf("%s\n", dest); // 输出 hello

    // strcat：拼接字符串（将 src 追加到 dest 末尾）
    strcat(dest, " world");
    printf("%s\n", dest); // 输出 hello world

    // strcmp：比较字符串
    // 相等返回 0，s1 < s2 返回负数，s1 > s2 返回正数
    printf("%d\n", strcmp("abc", "abc")); // 返回 0
    printf("%d\n", strcmp("abc", "abd")); // 输出：负数（"abc" < "abd"）

    // strstr：查找子串，返回首次出现位置的指针，找不到返回 NULL
    char *pos = strstr("hello world", "world");
    if (pos != NULL)
    {
        // 输出：world
        printf("%s\n", pos);
    }
}

// ====================================================================================================

/**
 * C++中的string
 */
void func3()
{
    string s = "hello, world!";

    // 长度（length 和 size 完全一样）
    // 输出：13
    cout << s.length() << endl;

    // 输出：13
    cout << s.size() << endl;

    // 通过下标访问单个字符
    // 输出：H
    cout << s[0] << endl;

    // 截取子串：substr(起始位置, 长度)
    // 输出：Hello
    cout << s.substr(0, 5) << endl;

    // 查找子串：find 返回首次出现的位置
    // 输出：7
    cout << s.find("world") << endl;

    // 找不到返回 string::npos
    if (s.find("xyz") == string::npos)
    {
        // 输出：not found
        cout << "not found" << endl;
    }

    // 字符串比较：直接用 == 就行
    string a = "hello";
    string b = "hello";
    // 输出：1
    cout << (a == b) << endl;

    // 字符串拼接：用 + 就行
    string c = a + " world";
    // 输出：hello world
    cout << c << endl;

    // 遍历每个字符
    // 输出：h e l l o
    for (char ch : a)
    {
        cout << ch << " ";
    }
    cout << endl;
}

/**
 * 字符串与数字转换
 */
void func4()
{
    // 字符串转 int
    int n = stoi("123");
    // 输出：123
    cout << n << endl;

    // 字符串转 long long
    long long big = stoll("1234567890123");
    // 输出：1234567890123
    cout << big << endl;

    // 数字转字符串
    string s = to_string(42);
    // 输出：42
    cout << s << endl;

    string s2 = to_string(3.14);
    // 输出：3.140000
    cout << s2 << endl;
}

/**
 * 字符判断与转换
 * <cctype> 提供了一组判断和转换单个字符的函数，在处理字符串的算法题中经常用到
 */
void func5()
{
    // isdigit：是否为数字字符 '0'-'9'
    // 输出：1
    cout << (isdigit('3') != 0) << endl;
    // 输出：0
    cout << (isdigit('a') != 0) << endl;

    // isalpha：是否为字母
    // 输出：1
    cout << (isalpha('a') != 0) << endl;

    // toupper / tolower：大小写转换
    // 输出：A
    cout << (char)toupper('a') << endl;
    // 输出：a
    cout << (char)tolower('A') << endl;

    // 常用技巧：字母转数字索引（a=0, b=1, ...）
    // 这在算法题中非常常见，比如用数组代替哈希表统计字母频率
    char letter = 'd';
    int index = letter - 'a';
    // 输出：3
    cout << index << endl;
}

int main()
{
    // func1();
    // func2();
    func3();
    // func4();
    // func5();

    return 0;
}