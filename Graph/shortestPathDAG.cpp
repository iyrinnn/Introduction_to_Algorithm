#include <bits/stdc++.h>
using namespace std;

/*
   Shortest Path in a Directed Acyclic Graph (DAG)
   Steps:
   1. Topologically sort the graph.
   2. Relax all edges in topological order.(take the nodes out of the stack and relax the edges
      KNOWN as RELAXATION for which first you need a distance array,
      initially marked as infinity make the source node distance as zero)
   3. If a node is never updated (distance = INT_MAX), mark it as -1 (unreachable).
*/

void dfs(int curr, vector<pair<int, int>> adj[], vector<bool> &vis, stack<int> &s)
{
    vis[curr] = true;
    for (auto it : adj[curr])
    {
        int v = it.first;
        if (!vis[v])
            dfs(v, adj, vis, s);
    }
    s.push(curr);
}

void topologicalSort(int v, vector<pair<int, int>> adj[], stack<int> &s)
{
    vector<bool> vis(v, false);
    for (int i = 0; i < v; i++)
        if (!vis[i])
            dfs(i, adj, vis, s);
}

vector<int> shortestPath(int n, int m, vector<vector<int>> &edges)
{
    // Step 1: Build adjacency list
    vector<pair<int, int>> adj[n];
    for (int i = 0; i < m; i++)
    {
        int u = edges[i][0];
        int v = edges[i][1];
        int wt = edges[i][2];
        adj[u].push_back({v, wt});
    }

    // Step 2: Topological sort
    stack<int> s;
    topologicalSort(n, adj, s);

    // Step 3: Initialize distances
    vector<int> dis(n, INT_MAX);
    dis[0] = 0; // assuming 0 as the source

    // Step 4: Relax edges in topological order
    while (!s.empty())
    {
        int node = s.top();
        s.pop();

        if (dis[node] != INT_MAX) // only process reachable nodes
        {
            for (auto it : adj[node])
            {
                int v = it.first;
                int wt = it.second;

                if (dis[node] + wt < dis[v])
                    dis[v] = dis[node] + wt;
            }
        }
    }

    // Step 5: Mark unreachable nodes as -1
    for (int i = 0; i < n; i++)
        if (dis[i] == INT_MAX)
            dis[i] = -1;

    return dis;
}

int main()
{
    int n = 6, m = 7;
    vector<vector<int>> edges = {
        {0, 1, 2},
        {0, 4, 1},
        {4, 5, 4},
        {4, 2, 2},
        {1, 2, 3},
        {2, 3, 6},
        {5, 3, 1}};

    vector<int> ans = shortestPath(n, m, edges);

    cout << "Shortest distances from node 0:\n";
    for (int i = 0; i < n; i++)
        cout << i << " -> " << ans[i] << endl;

    return 0;
}


/* Topological sort works for a special case — DAGs.
   Dijkstra’s works for the general case — any graph without negative weights.”*/