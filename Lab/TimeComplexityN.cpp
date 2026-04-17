#include <bits/stdc++.h>
using namespace std;
using namespace chrono;

int linearSearch(vector<int> &arr, int key)
{
    for (int i = 0; i < arr.size(); i++)
    {
        if (arr[i] == key)
        {
            return i;
        }
    }
    return -1;
}

int main()
{

    vector<int> arr;
    int i;
    for (i = 0; i < 600000; i++)
    {
        arr.push_back(i);
    }

    int key = i;

    auto start = high_resolution_clock::now();

    int index = linearSearch(arr, key);
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(end - start);

    cout << "Time taken: " << duration.count() << " microseconds" << endl;
}
