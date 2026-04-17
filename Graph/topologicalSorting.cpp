#include <bits/stdc++.h>
using namespace std;

void dfs(int curr, vector<int> adj[], vector<bool> &vis, stack<int> &s) //o(v+e)
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

void topologicalSort(int v, vector<int> adj[])
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
        cout << s.top() << " ";
        s.pop();
    }
    cout << endl;
}

int main()
{
    int v, e;
    cout << "Enter number of vertices: ";
    cin >> v;
    cout << "Enter number of edges: ";
    cin >> e;

    vector<int> adj[v]; // adjacency list

    cout << "Enter edges (u v) for directed graph:\n";
    for (int i = 0; i < e; i++)
    {
        int u, vtx;
        cin >> u >> vtx;
        adj[u].push_back(vtx);
    }

    topologicalSort(v, adj);

    return 0;
}
