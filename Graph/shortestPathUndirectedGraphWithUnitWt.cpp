#include <bits/stdc++.h>
using namespace std;

vector<int> shortestPath(vector<vector<int>> &edges, int n, int m, int src)
{
    // Step 1: Build adjacency list
    vector<int> adj[n];
    for (int i = 0; i < m; i++)
    {
        int u = edges[i][0];
        int v = edges[i][1];
        adj[u].push_back(v);
        adj[v].push_back(u); // remove this line if graph is directed
    }

    // Step 2: Distance array
    vector<int> dist(n, INT_MAX);
    dist[src] = 0;

    // Step 3: BFS
    queue<int> q;
    q.push(src);

    while (!q.empty())
    {
        int node = q.front();
        q.pop();

        for (auto it : adj[node])
        {
            if (dist[node] + 1 < dist[it])
            {
                dist[it] = dist[node] + 1;
                q.push(it);
            }
        }
    }

    // Step 4: Replace unreachable with -1
    for (int i = 0; i < n; i++)
    {
        if (dist[i] == INT_MAX)
            dist[i] = -1;
    }

    return dist;
}

int main()
{
    int n = 6, m = 7;
    vector<vector<int>> edges = {
        {0, 1}, {0, 2}, {1, 3}, {2, 4}, {4, 5}, {3, 5}, {1, 2}};
    int src = 0;

    vector<int> res = shortestPath(edges, n, m, src);
    for (int d : res)
        cout << d << " ";
}
