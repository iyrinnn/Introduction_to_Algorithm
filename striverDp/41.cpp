#include <bits/stdc++.h>
using namespace std;

int f(int ind, int prev_ind, vector<int> &arr, vector<vector<int>> &dp)
{
    int n = (int)arr.size();
    if (ind == n)
        return 0;

    if (dp[ind][prev_ind + 1] != -1)
        return dp[ind][prev_ind + 1];

    // not take
    int len = 0 + f(ind + 1, prev_ind, arr, dp);

    // take
    if (prev_ind == -1 || arr[ind] > arr[prev_ind])
    {
        len = max(len, 1 + f(ind + 1, ind, arr, dp));
    }

    return dp[ind][prev_ind + 1] = len;
}

int longestIncreasingSubsequence(vector<int> &arr)
{
    int n = (int)arr.size();
    vector<vector<int>> dp(n, vector<int>(n + 1, -1));
    return f(0, -1, arr, dp);
}

int main()
{
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    cout << longestIncreasingSubsequence(arr);
    return 0;
}
