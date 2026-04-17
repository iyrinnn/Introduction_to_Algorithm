#include <bits/stdc++.h>
#include <fstream>
#include <sstream>
using namespace std;

int longestCommonSubsequence(int i, int j, string &s1, string &s2, vector<vector<int>> &dp)
{

    if (i < 0 || j < 0)
    {
        return 0;
    }
    if (dp[i][j] != -1)
    {
        return dp[i][j];
    }

    if (s1[i] == s2[j])
    {
        dp[i][j] = 1 + longestCommonSubsequence(i - 1, j - 1, s1, s2, dp);
        return dp[i][j];
    }

    dp[i][j] = max(longestCommonSubsequence(i - 1, j, s1, s2, dp), longestCommonSubsequence(i, j - 1, s1, s2, dp));
    return dp[i][j];
}

int main()
{

    string filename1 = "irin.txt";
    ifstream file1(filename1);

    if (!file1.is_open())
    {
        cerr << "Failed to open file: " << filename1 << endl;
        return 1;
    }

    stringstream buffer1;
    buffer1 << file1.rdbuf();
    string fileContent1 = buffer1.str();
    file1.close();

    string filename2 = "asshifa.txt";
    ifstream file2(filename2);

    if (!file2.is_open())
    {
        cerr << "Failed to open file: " << filename2 << endl;
        return 1;
    }

    stringstream buffer2;
    buffer2 << file2.rdbuf();
    string fileContent2 = buffer2.str();
    file2.close();

    int n = fileContent1.size();
    int m = fileContent2.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));

    // cout << longestCommonSubsequence(n - 1, m - 1, fileContent1, fileContent2, dp) << " ";

    for (int i = 0; i <= n; i++)
        dp[i][0] = 0;
    for (int j = 0; j <= m; j++)
        dp[0][j] = 0;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (fileContent1[i - 1] == fileContent2[j - 1])
            {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            }
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }

    int len = dp[n][m];
    string s(len, ' ');
    int index = len - 1;

    int i = n, j = m;
    while (i > 0 && j > 0)
    {
        if (fileContent1[i - 1] == fileContent2[j - 1])
        {
            s[index] = fileContent1[i - 1];
            index--;
            i--;
            j--;
        }
        else if (dp[i - 1][j] > dp[i][j - 1])
        {
            i = i - 1;
        }
        else
        {
            j = j - 1;
        }
    }

    cout << s << endl;
}