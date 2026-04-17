#include <bits/stdc++.h>
using namespace std;

int knapsack(vector<int> &weight, vector<int> &value, int n, int maxWeight)
{

    // dp[i][w] = max value using items 0..i with capacity w
    vector<vector<int>> dp(n, vector<int>(maxWeight + 1, 0));

    // Base case: item 0
    for (int w = weight[0]; w <= maxWeight; w++)
    {
        dp[0][w] = value[0];
    }

    // Fill DP table
    for (int i = 1; i < n; i++)
    {
        for (int w = 0; w <= maxWeight; w++)
        {

            int notTake = dp[i - 1][w];
            int take = INT_MIN;

            if (weight[i] <= w)
            {
                take = value[i] + dp[i - 1][w - weight[i]];
            }

            dp[i][w] = max(take, notTake);
        }
    }

    return dp[n - 1][maxWeight];
}

int main()
{
    int n, maxWeight;
    cin >> n >> maxWeight;

    vector<int> weight(n), value(n);
    for (int i = 0; i < n; i++)
        cin >> weight[i];
    for (int i = 0; i < n; i++)
        cin >> value[i];

    cout << knapsack(weight, value, n, maxWeight);
    return 0;
}

#include <bits/stdc++.h>
using namespace std;

int knapsack(vector<int> wt, vector<int> val, int n, int maxWeight)
{
    vector<vector<int>> dp(n, vector<int>(maxWeight + 1, 0));

    // base case for item 0
    for (int w = wt[0]; w <= maxWeight; w++)
        dp[0][w] = val[0];

    for (int ind = 1; ind < n; ind++)
    {
        for (int w = 0; w <= maxWeight; w++)
        {

            int notTake = 0 + dp[ind - 1][w];
            int take = INT_MIN;

            if (wt[ind] <= w)
            {
                take = val[ind] + dp[ind - 1][w - wt[ind]];
            }

            dp[ind][w] = max(take, notTake);
        }
    }

    return dp[n - 1][maxWeight];
}

int main()
{
    int n, maxWeight;
    cin >> n >> maxWeight;

    vector<int> wt(n), val(n);
    for (int i = 0; i < n; i++)
        cin >> wt[i];
    for (int i = 0; i < n; i++)
        cin >> val[i];

    cout << knapsack(wt, val, n, maxWeight);
    return 0;
}
