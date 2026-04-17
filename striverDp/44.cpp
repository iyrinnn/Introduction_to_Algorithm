#include <bits/stdc++.h>
using namespace std;

vector<int> largestDivisibleSubset(vector<int> &nums)
{
    int n = nums.size();
    if (n == 0)
        return {};

    sort(nums.begin(), nums.end());

    vector<int> dp(n, 1), parent(n);
    for (int i = 0; i < n; i++)
        parent[i] = i;

    int maxLen = 1, lastIndex = 0;

    for (int i = 0; i < n; i++)
    {
        for (int prev = 0; prev < i; prev++)
        {
            if (nums[i] % nums[prev] == 0)
            {
                if (dp[prev] + 1 > dp[i])
                {
                    dp[i] = dp[prev] + 1;
                    parent[i] = prev;
                }
            }
        }
        if (dp[i] > maxLen)
        {
            maxLen = dp[i];
            lastIndex = i;
        }
    }

    // reconstruct answer
    vector<int> ans;
    while (parent[lastIndex] != lastIndex)
    {
        ans.push_back(nums[lastIndex]);
        lastIndex = parent[lastIndex];
    }
    ans.push_back(nums[lastIndex]);

    reverse(ans.begin(), ans.end());
    return ans;
}
