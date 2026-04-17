#include <bits/stdc++.h>
using namespace std;

bool bfs(int n, int source, int sink, vector<vector<int>> &updatedGraph, vector<int> &parent)
{
    vector<bool> visited(n, false);
    queue<int> q;

    visited[source] = true;
    q.push(source);
    parent[source] = -1;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (int i = 0; i < n; i++)
        {
            if (visited[i] == false && updatedGraph[u][i] > 0)
            {
                q.push(i);
                parent[i] = u;
                visited[i] = true;
            }
        }
    }

    return visited[sink] == true;
}

int maxFLow(int n, int source, int sink, vector<vector<int>> &graph)
{
    int maximumFlow = 0;
    vector<vector<int>> updatedGraph;
    updatedGraph = graph;

    vector<int> parent(n);

    while (1)
    {
        if (bfs(n, source, sink, updatedGraph, parent) == false)
        {
            break;
        }

        int pathMinimum = INT_MAX;

        for (int v = sink; v != source; v = parent[v])
        {
            int u = parent[v];

            pathMinimum = min(pathMinimum, updatedGraph[u][v]);
        }

        for (int v = sink; v != source; v = parent[v])
        {
            int u = parent[v];
            updatedGraph[u][v] -= pathMinimum;
            updatedGraph[v][u] += pathMinimum;
        }

        maximumFlow += pathMinimum;
    }

    return maximumFlow;
}

int main()
{
    int n;
    cin >> n;

    int s, t, e;
    cin >> s >> t >> e;
    s--;
    t--;

    vector<vector<int>> graph(n, vector<int>(n, 0));

    for (int i = 0; i < e; i++)
    {
        int u;
        int v;
        cin >> u;
        cin >> v;
        u--;
        v--;

        int w;
        cin >> w;
        graph[u][v] += w;
        graph[v][u] += w;
    }

    int maximumFlow = maxFLow(n, s, t, graph);
    cout << "The bandwidth is " << maximumFlow << endl;
}