#include <bits/stdc++.h>
using namespace std;

int main()
{
    int t;
    cin >> t;

    int countIndex = 0;
    vector<int> ans(t);

    while (t--)
    {
        int n, k;
        cin >> n >> k;

        vector<int> arr(n);

        for (int i = 0; i < n; i++)
        {
            cin >> arr[i];
        }

        sort(arr.begin(), arr.end());
        int currentMEX = 0;
        for (int i = 0; i < n; i++)
        {
            if (arr[i] != i)
            {
                currentMEX = i;
                break;
            }
        }

        ans[countIndex++] = k - currentMEX;
    }

    for (int i = 0; i < countIndex; i++)
    {
        cout << ans[i] << endl;
    }
}