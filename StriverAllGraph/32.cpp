#include <bits/stdc++.h>
using namespace std;

vector<int> dijkstra(int v, vector<vector<pair<int, int>>> &adj, int source)
{

    const int INF = 1e9;
    vector<int> dist(v, INF);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dist[source] = 0;
    pq.push({0, source});

    while (!pq.empty())
    {
        int dis = pq.top().first;
        int node = pq.top().second;
        pq.pop();

        for (auto &it : adj[node])
        {
            int adjNode = it.first;
            int edgeWeight = it.second;

            if (dis + edgeWeight < dist[adjNode])
            {
                dist[adjNode] = dis + edgeWeight;
                pq.push({dist[adjNode], adjNode});
            }
        }
    }

    return dist;
}

int main()
{
    int v, e;
    cin >> v >> e;

    vector<vector<pair<int, int>>> adj(v);

    for (int i = 0; i < e; i++)
    {
        int u, vv, w;
        cin >> u >> vv >> w;

        adj[u].push_back({vv, w});
        // for undirected:
        // adj[vv].push_back({u, w});
    }

    int source;
    cin >> source;

    vector<int> dist = dijkstra(v, adj, source);

    for (int i = 0; i < v; i++)
    {
        cout << "Node " << i << ": " << dist[i] << "\n";
    }

    return 0;
}
