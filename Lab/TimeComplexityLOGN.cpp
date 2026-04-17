#include <bits/stdc++.h>
using namespace std;
using namespace chrono;

long long binarySearch(long long N, long long key)
{
    long long left = 0, right = N - 1;

    while (left <= right)
    {
        long long mid = left + (right - left) / 2;

        if (mid == key)
            return mid;
        else if (mid < key)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return -1;
}

int main()
{
    long long N = 60000000000000;
    long long key = N - 1;

    auto start = high_resolution_clock::now();
    long long index = binarySearch(N, key);
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(end - start);

    cout << "Index found: " << index << endl;
    cout << "Time taken: " << duration.count() << " microseconds" << endl;
}
