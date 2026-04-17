#include <bits/stdc++.h>
using namespace std;

int longestIncreasingSubsequence(vector<int> &arr)
{
    int n = (int)arr.size();

    // dp[ind][prev_ind+1]
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

    for (int ind = n - 1; ind >= 0; ind--)
    {
        for (int prev_ind = ind - 1; prev_ind >= -1; prev_ind--)
        {

            int len = 0 + dp[ind + 1][prev_ind + 1];

            if (prev_ind == -1 || arr[ind] > arr[prev_ind])
            {
                len = max(len, 1 + dp[ind + 1][ind + 1]);
            }

            dp[ind][prev_ind + 1] = len;
        }
    }

    return dp[0][0];
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

#include <bits/stdc++.h>
using namespace std;

vector<int> printLIS(vector<int> &arr)
{
    int n = arr.size();

    vector<int> dp(n, 1), hash(n);
    int maxi = 1, lastIndex = 0;

    for (int i = 0; i < n; i++)
    {
        hash[i] = i;
        for (int prev = 0; prev < i; prev++)
        {
            if (arr[prev] < arr[i] && dp[prev] + 1 > dp[i])
            {
                dp[i] = dp[prev] + 1;
                hash[i] = prev;
            }
        }
        if (dp[i] > maxi)
        {
            maxi = dp[i];
            lastIndex = i;
        }
    }

    // Backtracking LIS
    vector<int> lis;
    lis.push_back(arr[lastIndex]);

    while (hash[lastIndex] != lastIndex)
    {
        lastIndex = hash[lastIndex];
        lis.push_back(arr[lastIndex]);
    }

    reverse(lis.begin(), lis.end());
    return lis;
}

int main()
{
    int n;
    cin >> n;

    vector<int> arr(n);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    vector<int> lis = printLIS(arr);

    // Print LIS
    for (int x : lis)
        cout << x << " ";
    cout << endl;

    return 0;
}
