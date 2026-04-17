#include <bits/stdc++.h>
using namespace std;

/*
   can be solved using detect cycle in directed graph using dfs
   ore can be solved using toposort (bfs)....using topo as they also
   asked for the ordering
*/

void dfs(int curr, vector<int> adj[], vector<bool> &vis, stack<int> &s) // o(v+e)
{
    vis[curr] = true;

    for (auto it : adj[curr])
    {
        if (!vis[it])
        {
            dfs(it, adj, vis, s);
        }
    }
    s.push(curr);
}

void topologicalSort(int v, vector<int> adj[], vector<int> &topoSort)
{
    vector<bool> vis(v, false);
    stack<int> s;
    for (int i = 0; i < v; i++)
    {
        if (!vis[i])
        {
            dfs(i, adj, vis, s);
        }
    }

    while (s.size() > 0)
    {
        topoSort.push_back(s.top());
        s.pop();
    }
    return;
}

bool isPossible(int v, vector<pair<int, int>> &prerequisites)
{
    vector<int> adj[v];
    for (auto it : prerequisites)
    {
        adj[it.first].push_back(it.second);
    }

    vector<int> topoSort;
    topologicalSort(v, adj, topoSort);

    if (topoSort.size() == v)
    {
        return true;
    }

    return false;
}