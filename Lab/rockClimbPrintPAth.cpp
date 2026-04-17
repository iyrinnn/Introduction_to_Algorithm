#include <bits/stdc++.h>
using namespace std;
void printBest(int i, int j, int m, vector<vector<int>> &dp, vector<vector<int>> &arr)
{

    if (i == 0 || j == 0 || j == m + 1)
        return;

    if (dp[i - 1][j - 1] <= dp[i - 1][j] && dp[i - 1][j - 1] <= dp[i - 1][j + 1])
    {
        printBest(i - 1, j - 1, m, dp, arr);
    }
    else if (dp[i - 1][j] <= dp[i - 1][j - 1] && dp[i - 1][j] <= dp[i - 1][j + 1])
    {
        printBest(i - 1, j, m, dp, arr);
    }
    else if (dp[i - 1][j + 1] <= dp[i - 1][j - 1] && dp[i - 1][j + 1] <= dp[i - 1][j])
    {
        printBest(i - 1, j + 1, m, dp, arr);
    }
    cout << dp[i][j] << " ";
}

int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> arr(n, vector<int>(m));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> arr[i][j];
        }
    }

    vector<vector<int>> dp(n + 1, vector<int>(m + 2, 0));

    for (int i = 0; i <= n; i++)
    {
        dp[i][0] = INT_MAX;
        dp[i][m + 1] = INT_MAX;
    }

    for (int j = 1; j <= m; j++)
        dp[0][j] = 0;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            int above = dp[i - 1][j];
            int aboveToTheLeft = dp[i - 1][j - 1];
            int aboveToTheRight = dp[i - 1][j + 1];

            dp[i][j] = arr[i - 1][j - 1] + min(above, min(aboveToTheLeft, aboveToTheRight));
        }
    }

    int minCost = INT_MAX;
    int colIndex = 0;
    for (int j = 0; j < m + 2; j++)
    {
        if (dp[n][j] < minCost)
        {
            minCost = dp[n][j];
            colIndex = j;
        }
    }

    cout << minCost << endl;

    printBest(n, colIndex, m, dp, arr);

    return 0;
}
