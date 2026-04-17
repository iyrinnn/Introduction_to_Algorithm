#include <bits/stdc++.h>
using namespace std;

long long maximumNonAdjacentSum(vector<int> &nums)
{
    int n = nums.size();
    if (n == 0)
        return 0;
    if (n == 1)
        return nums[0];

    long long prev = nums[0];
    long long prev2 = 0;

    for (int i = 1; i < n; i++)
    {
        long long take = nums[i];
        if (i > 1)
            take += prev2;

        long long notTake = prev;
        long long curi = max(take, notTake);

        prev2 = prev;
        prev = curi;
    }
    return prev;
}

long long houseRobber(vector<int> &valueInHouse)
{
    int n = valueInHouse.size();
    if (n == 1)
        return valueInHouse[0];

    vector<int> temp1, temp2;

    for (int i = 0; i < n; i++)
    {
        if (i != 0)
            temp1.push_back(valueInHouse[i]); // exclude first
        if (i != n - 1)
            temp2.push_back(valueInHouse[i]); // exclude last
    }

    return max(maximumNonAdjacentSum(temp1),
               maximumNonAdjacentSum(temp2));
}
