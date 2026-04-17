#include <bits/stdc++.h>
using namespace std;

int f(int ind, int N, vector<int> &price, vector<vector<int>> &dp)
{
    if (ind == 0)
    {
        return N * price[0];
    }

    if (dp[ind][N] != -1)
        return dp[ind][N];

    int notTake = 0 + f(ind - 1, N, price, dp);

    int take = INT_MIN;
    int rodLength = ind + 1;

    if (rodLength <= N)
    {
        take = price[ind] + f(ind, N - rodLength, price, dp);
    }

    return dp[ind][N] = max(take, notTake);
}

int cutRod(vector<int> &price, int n)
{
    vector<vector<int>> dp(n, vector<int>(n + 1, -1));
    return f(n - 1, n, price, dp);
}

// ------- for testing ----------
int main()
{
    int n;
    cin >> n;
    vector<int> price(n);
    for (int i = 0; i < n; i++)
        cin >> price[i];

    cout << cutRod(price, n) << "\n";
    return 0;
}
#include <bits/stdc++.h>
using namespace std;

int cutRod(vector<int> &price, int n)
{
    vector<int> dp(n + 1, 0);

    // Base case: using only length-1 rods
    for (int N = 0; N <= n; N++)
    {
        dp[N] = N * price[0];
    }

    for (int ind = 1; ind < n; ind++)
    {
        for (int N = 0; N <= n; N++)
        {
            int notTake = dp[N];
            int take = INT_MIN;

            int rodLength = ind + 1;
            if (rodLength <= N)
            {
                take = price[ind] + dp[N - rodLength];
            }

            dp[N] = max(take, notTake);
        }
    }

    return dp[n];
}

// -------- main function ----------
int main()
{
    int n;
    cin >> n;

    vector<int> price(n);
    for (int i = 0; i < n; i++)
    {
        cin >> price[i];
    }

    cout << cutRod(price, n) << endl;
    return 0;
}
