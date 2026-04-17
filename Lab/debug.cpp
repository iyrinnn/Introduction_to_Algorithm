#include <bits/stdc++.h>
#include <filesystem>
using namespace std;
using namespace std::filesystem;

int longestCommonSubsequence(int i, int j, vector<string> &s1, vector<string> &s2, vector<vector<int>> &dp)
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
    string folderPath = "E:/03_THIRD SEMESETER/Introduction to Algorithm/Lab";
    if (!exists(folderPath))
    {
        cout << "Folder not found!" << endl;
        return 0;
    }

    int fileIndex = 0;
    vector<vector<string>> fileContents;
    for (const auto &entry : directory_iterator(folderPath))
    {
        string filename = entry.path().string();

        ifstream file(filename);
        if (!file.is_open())
        {
            cout << "Failed to open file: " << filename << endl;
            continue;
        }

        stringstream buffer;
        buffer << file.rdbuf();
        file
    }

    string filename1 = "irin.txt";
    ifstream file1(filename1);

    if (!file1.is_open())
    {
        cerr << "Failed to open file: " << filename1 << endl;
        return 1;
    }

    stringstream buffer1;
    buffer1 << file1.rdbuf();
    vector<string> fileContent1;
    string intermediate;
    while (buffer1 >> intermediate)
    {
        fileContent1.push_back(intermediate);
    }
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
    vector<string> fileContent2;

    while (buffer2 >> intermediate)
    {
        fileContent2.push_back(intermediate);
    }

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
    vector<string> s;
    int index = len - 1;

    int i = n, j = m;
    while (i > 0 && j > 0)
    {
        if (fileContent1[i - 1] == fileContent2[j - 1])
        {
            s.push_back(fileContent1[i - 1]);
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

    cout << dp[n][m] << endl;
    reverse(s.begin(), s.end());

    for (auto it : s)
    {
        cout << it << endl;
    }
}