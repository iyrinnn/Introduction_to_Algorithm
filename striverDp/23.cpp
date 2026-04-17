#include <bits/stdc++.h>
using namespace std;

int unboundedKnapsack(int n, int W, vector<int> &val, vector<int> &wt)
{

    // dp[w] = maximum value for capacity w
    vector<int> dp(W + 1, 0);

    // Base case: using only item 0
    for (int w = 0; w <= W; w++)
    {
        dp[w] = (w / wt[0]) * val[0];
    }

    // Process remaining items
    for (int i = 1; i < n; i++)
    {
        for (int w = 0; w <= W; w++)
        {

            int notTake = dp[w];
            int take = INT_MIN;

            if (wt[i] <= w)
            {
                take = val[i] + dp[w - wt[i]]; // NOTE: dp[w - wt[i]]
            }

            dp[w] = max(take, notTake);
        }
    }

    return dp[W];
}

int main()
{
    int n, W;
    cin >> n >> W;

    vector<int> wt(n), val(n);
    for (int i = 0; i < n; i++)
        cin >> wt[i];
    for (int i = 0; i < n; i++)
        cin >> val[i];

    cout << unboundedKnapsack(n, W, val, wt);
    return 0;
}
