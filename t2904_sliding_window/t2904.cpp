#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string shortestBeautifulSubstring(string s, int k) {
        // 如果字符串中1的数量总数小于k，直接返回空字符串
        if (count(s.begin(), s.end(), '1') < k) {
            return "";
        }

        int left = 0;
        int right = 0;
        // 字符串中'1'的长度
        int cnt = 0;
        string ans = s;
        while (right < s.length()) {
            if (s[right] == '1') {
                cnt++;
            }
            right++;
            
            // 判断窗口左侧收缩
            while (cnt > k || s[left] == '0') {
                if (s[left] == '1') {
                    cnt--;
                }
                left++;
            }

            // 在窗口外执行更新逻辑
            if (cnt == k) {
                string t = s.substr(left, right - left);
                if (t.length() < ans.length() || t.length() == ans.length() && t < ans) {
                    ans = move(t);
                }
            }
        }
        return ans;
    }
};

int main()
{
    Solution solution;

    // "11001"
    string ans = solution.shortestBeautifulSubstring("100011001", 3);
    cout << ans << endl;

    // "11"
    string ans2 = solution.shortestBeautifulSubstring("1011", 2);
    cout << ans2 << endl;

    // ""
    string ans3 = solution.shortestBeautifulSubstring("000", 1);
    cout << ans3 << endl;

    // "11111111001000101"
    string ans4 = solution.shortestBeautifulSubstring("111111110010001010", 11);
    cout << ans4 << endl;

    return 0;
}
