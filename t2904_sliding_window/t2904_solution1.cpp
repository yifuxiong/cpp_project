#include <bits/stdc++.h>
using namespace std;

// leetcode官方解法：滑动窗口
class Solution {
public:
    string shortestBeautifulSubstring(string s, int k) {
        // 如果字符串中1的数量总数小于k，直接返回空字符串
        // C++20 才有的 `ranges::count()`
        if (count(s.begin(), s.end(), '1') < k) {
            return "";
        }

        string ans = s;
        int cnt = 0;
        for (int left = 0, right = 0; right < s.length(); right++) {
            cnt += s[right] - '0';
            while (cnt > k || s[left] == '0') {
                cnt -= s[left] - '0';
                left++;
            }
            if (cnt == k) {
                string t = s.substr(left, right - left + 1);
                if (t.length() < ans.length() || t.length() == ans.length() && t < ans) {
                    ans = move(t);
                }
            }
        }
        // 对 `std::string` 来说，拷贝意味着要**重新申请内存 + 逐字符复制**
        // 而移动只是把 `t` 内部指向堆内存的指针 "过户" 给 `ans`，`t` 变成空串。所以 `move` 省掉了一次深拷贝，更高效。
        return ans;
    }
};

int main()
{
    Solution solution;
    // 在这里调用测试你的函数
    string ans = solution.shortestBeautifulSubstring("100011001", 3);
    cout << ans << endl;
    return 0;
}

/**
 * 
 * ## 为什么这里可以安全地 move
 * 
 * 关键点：**`t` 是循环体内的局部变量，用完这次迭代就销毁了**。把它的内存移给 `ans` 后，`t` 变空也没关系，反正不会再用了。所以：
 * - 这里 `ans = move(t);` 等价于 `ans = t;` 的语义（结果一样），只是省了次拷贝。
 * - 如果你**之后还要用 `t`**，就不能 move（会把 `t` 掏空）。
 */