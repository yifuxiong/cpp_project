#include <iostream>
using namespace std;

class Solution
{
public:
    const int mod = 1e9 + 7;

    long long quickPow(long long a, long long e)
    {
        long long result = 1;
        while (e > 0)
        {
            if (e & 1)
            {
                result = result * a % mod;
            }
            a = a * a % mod;
            e = (e >> 1);
        }
        return result;
    }

    int numberOfSets(int n, int k)
    {
        int m = 2 * k;
        long long numerator = 1;
        long long denominator = 1;
        // n + k - 1个数里面选出2k个，公式：c(n + k - 1)(2k)
        for (int i = 1; i <= m; i++)
        {
            numerator = numerator * (n + k - i) % mod;
            denominator = denominator * i % mod;
        }
        return numerator * quickPow(denominator, mod - 2) % mod;
    }
};
