#include <bits/stdc++.h>
using namespace std;

class DisjointSet
{
private:
    vector<int> parent, size;

public:
    // Constructor: initialize DSU with n elements
    DisjointSet(int n)
    {
        parent.resize(n + 1);
        size.assign(n + 1, 1);

        for (int i = 1; i <= n; i++)
        {
            parent[i] = i; // each node is its own parent
        }
    }

    // FIND with path compression
    int find(int x)
    {
        if (parent[x] == x)
            return x;
        return parent[x] = find(parent[x]); // path compression
    }

    // UNION by size
    void unite(int a, int b)
    {
        a = find(a);
        b = find(b);

        if (a != b)
        {
            if (size[a] < size[b])
                swap(a, b); // ensure a is larger
            parent[b] = a;  // attach b under a
            size[a] += size[b];
        }
    }

    // Optional: check if two nodes are in the same set
    bool sameSet(int a, int b)
    {
        return find(a) == find(b);
    }
};

int main()
{
    DisjointSet ds(7); // example with 7 elements

    ds.unite(1, 2);
    ds.unite(2, 3);
    ds.unite(4, 5);

    cout << ds.find(3) << "\n";       // representative of 3
    cout << ds.sameSet(1, 3) << "\n"; // true
    cout << ds.sameSet(1, 4) << "\n"; // false

    ds.unite(3, 5);
    cout << ds.sameSet(1, 5) << "\n"; // now true

    return 0;
}
