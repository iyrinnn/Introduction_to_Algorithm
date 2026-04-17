#include <bits/stdc++.h>
using namespace std;

int f(int ind, vector<int> &nums, vector<int> &dp)
{
    if (ind == 0)
        return nums[0];
    if (ind < 0)
        return 0;

    if (dp[ind] != -1)
        return dp[ind];

    int pick = nums[ind] + f(ind - 2, nums, dp);
    int notPick = 0 + f(ind - 1, nums, dp);

    return dp[ind] = max(pick, notPick);
}

int maximumNonAdjacentSum(vector<int> &nums)
{
    int n = nums.size();
    vector<int> dp(n, -1);
    return f(n - 1, nums, dp);
}

int main()
{
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; i++)
        cin >> nums[i];

    cout << maximumNonAdjacentSum(nums) << endl;
    return 0;
}

#include <bits/stdc++.h>
using namespace std;

int maximumNonAdjacentSum(vector<int> &nums)
{
    int n = nums.size();
    if (n == 0)
        return 0;
    if (n == 1)
        return nums[0];

    int prev = nums[0];
    int prev2 = 0;

    for (int i = 1; i < n; i++)
    {
        int pick = nums[i] + prev2;
        int notPick = prev;

        int cur = max(pick, notPick);
        prev2 = prev;
        prev = cur;
    }
    return prev;
}

int main()
{
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; i++)
        cin >> nums[i];

    cout << maximumNonAdjacentSum(nums) << endl;
    return 0;
}
