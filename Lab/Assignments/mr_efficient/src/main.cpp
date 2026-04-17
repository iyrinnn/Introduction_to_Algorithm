#include <bits/stdc++.h>

using namespace std;
struct Dhakastreet
{
    double latitude;
    double longitude;
    double altitude;
    double distance;
};

vector<vector<string>> fileRead(string fileName)
{
    ifstream file(fileName);

    if (!file.is_open())
    {
        cerr << "Failed to open file: " << fileName << endl;
    }

    vector<vector<string>> dataset;
    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        vector<string> row;
        string cell;

        while (getline(ss, cell, ','))
        {
            row.push_back(cell);
        }

        dataset.push_back(row);
    }

    file.close();
    return dataset;
}

vector<Dhakastreet> readDhakaStreets(string fileName)
{
    auto data = fileRead(fileName);
    vector<Dhakastreet> streets;

    
    for (size_t i = 0; i < data.size(); i++)
    {
        if (data[i].size() >= 4)
        {
            Dhakastreet ds;
            ds.latitude = stod(data[i][0]);
            ds.longitude = stod(data[i][1]);
            ds.altitude = stod(data[i][2]);
            ds.distance = stod(data[i][3]);
            streets.push_back(ds);
        }
    }

    return streets;
}



vector<int> dijkstra(int V, vector<vector<int>> adj[], int S)
{
    // Min-heap: {distance, node}
    priority_queue<pair<int, int>,
                    vector<pair<int, int>>,
                    greater<pair<int, int>>> pq;

    vector<int> dist(V, 1e9);   // Initialize distances with large value
    dist[S] = 0;

    pq.push({0, S});

    while (!pq.empty())
    {
        int dis = pq.top().first;
        int node = pq.top().second;
        pq.pop();

        for (auto it : adj[node])
        {
            int adjNode = it[0];
            int edgeWeight = it[1];

            if (dis + edgeWeight < dist[adjNode])
            {
                dist[adjNode] = dis + edgeWeight;
                pq.push({dist[adjNode], adjNode});
            }
        }
    }

    return dist;
}


