#include <bits/stdc++.h>
using namespace std;

class DisjointSet
{
    vector<int> size, parent;

public:
    DisjointSet(int n)
    {
        parent.resize(n + 1);
        size.resize(n + 1, 1);
        for (int i = 0; i <= n; i++)
        {
            parent[i] = i;
        }
    }

    int find(int x)
    {
        if (parent[x] == x)
            return x;
        return parent[x] = find(x);
    }

    void unite(int u, int v)
    {
        int pu = find(u);
        int pv = find(v);

        if (pu != pv)
        {
            if (size[pu] < size[pv])
            {
                swap(pu, pv);
            }
            parent[pv] = pu;
            size[pu] += size[pv];
        }
    }
};

void buildingRoads(int n, vector<pair<int, int>> &edges)
{
    DisjointSet ds(n);
    int numberOfOperations = 0;
    vector<pair<int, int>> newRoads;

    // sort(edges.begin(), edges.end());  this is of no use

    for (auto it : edges)
    {
        int u = it.first;
        int v = it.second;
        ds.unite(u, v);
    }

    for

    cout << numberOfOperations << endl;
    for (auto it : newRoads)
    {
        cout << it.first << " " << it.second << endl;
    }
}

int main()
{
    int n, m;
    cin >> n >> m;

    vector<pair<int, int>> edges;

    for (int i = 0; i < m; i++)
    {
        int u;
        int v;
        cin >> u >> v;
        edges.push_back({u, v});
    }

    buildingRoads(n, edges);
}