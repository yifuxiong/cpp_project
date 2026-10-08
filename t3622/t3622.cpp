#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> getN(int n) {
        vector<int> nums;
        while (n > 0) {
            nums.push_back(n % 10);
            n /= 10;
        }
        return nums;
    }

    bool checkDivisibility(int n) {
        int sum = 0;
        int mul = 1;
        vector<int> nums = getN(n);
        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i];
            mul *= nums[i];
        }
        return n % (sum + mul) == 0;
    }
};

int main()
{
    Solution solution;
    // 在这里调用测试你的函数
    bool res = solution.checkDivisibility(8);
    cout << res << endl;
    return 0;
}