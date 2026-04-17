#include <bits/stdc++.h>
using namespace std;

bool isCycleDirDFS(int curr, vector<bool> &vis, vector<bool> &recpath, vector<int> adj[])
{ // o(v+e)
    vis[curr] = true;
    recpath[curr] = true;

    for (int v : adj[curr])
    {
        if (!vis[v])
        {
            if (isCycleDirDFS(v, vis, recpath, adj))
            {
                return true;
            }
        }
        else if (recpath[v])
        {
            return true;
        }
    }

    recpath[curr] = false;
    return false;
}

bool isCycle(int v, vector<int> adj[])
{
    vector<bool> vis(v, false);
    vector<bool> recpath(v, false);

    for (int i = 0; i < v; i++)
    {
        if (!vis[i])
        {
            if (isCycleDirDFS(i, vis, recpath, adj))
            {
                return true;
            }
        }
    }

    return false;
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

    if (isCycle(v, adj))
    {
        cout << "Cycle detected!" << endl;
    }
    else
    {
        cout << "No cycle found." << endl;
    }

    return 0;
}
