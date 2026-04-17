#include <bits/stdc++.h>
using namespace std;

int editOperation(int i, int j, string &s1, string &s2, vector<vector<int>> &dp)
{

    if (i < 0)
        return j + 1;
    if (j < 0)
        return i + 1;

    if (dp[i][j] != -1)
        return dp[i][j];

    if (s1[i] == s2[j])
    {
        dp[i][j] = editOperation(i - 1, j - 1, s1, s2, dp);
    }
    else
    {
        int deleteOp = editOperation(i - 1, j, s1, s2, dp);
        int insertOp = editOperation(i, j - 1, s1, s2, dp);
        int replaceOp = editOperation(i - 1, j - 1, s1, s2, dp);
        dp[i][j] = 1 + min(deleteOp, min(insertOp, replaceOp));
    }

    return dp[i][j];
}

int editDistance(string s1, string s2)
{
    int n = s1.size();
    int m = s2.size();

    vector<vector<int>> dp(n, vector<int>(m, -1));

    return editOperation(n - 1, m - 1, s1, s2, dp);
}

int main()
{
    string word1, word2;
    cout << "Enter two words: ";
    cin >> word1 >> word2;

    int ans = editDistance(word1, word2);
    cout << "Minimum operations: " << ans << endl;

    return 0;
}
