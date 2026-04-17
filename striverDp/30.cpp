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

int canYouMake(string &str, string &ptr)
{
    return str.size() + ptr.size() - 2 * lcs(str, ptr);
}

int main()
{
    int t;
    cin >> t;

    while (t--)
    {
        string str, ptr;
        cin >> str >> ptr;
        cout << canYouMake(str, ptr) << endl;
    }

    return 0;
}
