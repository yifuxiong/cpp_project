#include <bits/stdc++.h>
using namespace std;

/**
 * Definition for singly-linked list.
 */
struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution
{
public:
    vector<int> nodesBetweenCriticalPoints(ListNode *head)
    {
        vector<int> ans = {};


        return ans;
    }
};

int main()
{
    Solution solution;

    ListNode *head = nullptr;
    vector<int> nodes = solution.nodesBetweenCriticalPoints(head);

    return 0;
}