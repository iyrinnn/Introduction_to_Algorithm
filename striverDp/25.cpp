#include <bits/stdc++.h>
using namespace std;

int f(int i, int j, string &s, string &t, vector<vector<int>> &dp)
{
    if (i < 0 || j < 0)
        return 0;

    if (dp[i][j] != -1)
        return dp[i][j];

    if (s[i] == t[j])
        return dp[i][j] = 1 + f(i - 1, j - 1, s, t, dp);

    return dp[i][j] = max(
               f(i - 1, j, s, t, dp),
               f(i, j - 1, s, t, dp));
}

int lcs(string s, string t)
{
    int n = s.size(), m = t.size();
    vector<vector<int>> dp(n, vector<int>(m, -1));
    return f(n - 1, m - 1, s, t, dp);
}

int main()
{
    string s, t;
    cin >> s >> t;
    cout << lcs(s, t);
    return 0;
}

#include <bits/stdc++.h>
using namespace std;

int lcs(string s, string t)
{
    int n = s.size();
    int m = t.size();

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

    return dp[n][m];
}

int main()
{
    string s, t;
    cin >> s >> t;
    cout << lcs(s, t);
    return 0;
}
