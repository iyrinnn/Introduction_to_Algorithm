#include <bits/stdc++.h>
using namespace std;

int main()
{
    string s, t;
    cin >> s >> t;

    int n = s.size();
    int m = t.size();

    // Step 1: Build DP table for LCS length
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (s[i - 1] == t[j - 1])
                dp[i][j] = 1 + dp[i - 1][j - 1];
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }

    // Step 2: Length of LCS
    int len = dp[n][m];

    // Step 3: Create result string filled with placeholders
    string ans = "";
    for (int i = 0; i < len; i++)
        ans += '$';

    // Step 4: Backtrack to construct LCS
    int index = len - 1;
    int i = n, j = m;

    while (i > 0 && j > 0)
    {
        if (s[i - 1] == t[j - 1])
        {
            ans[index] = s[i - 1];
            index--;
            i--;
            j--;
        }
        else if (dp[i - 1][j] > dp[i][j - 1])
        {
            i--;
        }
        else
        {
            j--;
        }
    }

    // Step 5: Print LCS
    cout << ans;
    return 0;
}
