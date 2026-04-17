#include <bits/stdc++.h>
using namespace std;

int main()
{
    int t;
    cin >> t;
    vector<int> ans(t);
    int T = t;
    while (t--)
    {
        int n;
        cin >> n;
        vector<int> arr(n);

        int minusOneCOunt = 0;
        int oneCount = 0;
        int zeroCount = 0;
        for (int i = 0; i < n; i++)
        {
            cin >> arr[i];

            if (arr[i] == -1)
                minusOneCOunt++;
            else if (arr[i] == 1)
                oneCount++;
            else
                zeroCount++;
        }

        int numberOfOperations = 0;

        if (zeroCount != 0)
            numberOfOperations = numberOfOperations + zeroCount;
        if (minusOneCOunt % 2 == 1)
            numberOfOperations += 2;

        ans[T - t - 1] = numberOfOperations;
    }

    for (int i = 0; i < T; i++)
    {
        cout << ans[i] << endl;
    }
}
