#include <bits/stdc++.h>
using namespace std;

int main()
{
    int t;
    cin >> t;
    int T = t;
    vector<int> ans(t);

    while (t--)
    {
        int n;
        cin >> n;

        vector<int> arr(n);
        for (int i = 0; i < n; i++)
        {
            cin >> arr[i];
        }

        sort(arr.begin(), arr.end());

        int maxDiff = 0;
        for (int i = 0; i < n - 1; i += 2)
        {
            int currentDiff = abs(arr[i + 1] - arr[i]);
            maxDiff = max(maxDiff, currentDiff);
        }

        ans[T - (t + 1)] = maxDiff;
    }

    for (int i = 0; i < T; i++)
    {
        cout << ans[i] << endl;
    }
}