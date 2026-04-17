#include <bits/stdc++.h>
using namespace std;

int minCost(int i, int j, int n, int m, vector<vector<int>> &dp, vector<vector<int>> &arr)
{
    if (j < 0 || j >= m)
    {
        return INT_MAX;
    }
    if (i == 0)
    {
        return dp[i][j] = arr[i][j];
    }

    if (dp[i][j] != 0)
        return dp[i][j];

    int above = minCost(i - 1, j, n, m, dp, arr);
    int aboveToTheLeft = minCost(i - 1, j - 1, n, m, dp, arr);
    int aboveToTheRight = minCost(i - 1, j + 1, n, m, dp, arr);

    dp[i][j] = min(above, min(aboveToTheLeft, aboveToTheRight)) + arr[i][j];
    return dp[i][j];
}

int rockClimbing(int n, int m, vector<vector<int>> &arr)
{
    int cost = INT_MAX;

    vector<vector<int>> dp(n, vector<int>(m, 0));
    for (int j = 0; j < m; j++)
    {
        int currentCost = minCost(n - 1, j, n, m, dp, arr);
        cost = min(cost, currentCost);
    }

    return cost;
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

    int result = rockClimbing(n, m, arr);

    cout << result << endl;

    return 0;
}
