#include <bits/stdc++.h>
using namespace std;

int maxSum(int n, vector<int> &arr, vector<int> &dp, stack<int> &ans)
{
    if (dp[n] != -1)
        return dp[n];

    if (n == 0)
        return dp[n] = arr[0];

    if (n == 1)
        return dp[n] = max(arr[0], arr[1]);

    int include = maxSum(n - 2, arr, dp, ans) + arr[n];
    int exclude = maxSum(n - 1, arr, dp, ans);

    if (include > exclude)
        ans.push(arr[n]);

    return dp[n] = max(include, exclude);
}

int main()
{
    vector<int> arr = {15, 1, 2, 3, 4, 5, 6, 7, 8};
    vector<int> dp(arr.size(), -1);
    stack<int> ans;

    int mySum = maxSum(arr.size() - 1, arr, dp, ans);

    cout << "Maximum sum: " << mySum << endl;
    cout << "Elements included: ";
    while (!ans.empty())
    {
        cout << ans.top() << " ";
        ans.pop();
    }

    return 0;
}
