#pragma once

#include <vector>
#include <string>
#include <cmath>
using namespace std;

struct Node
{
    int id;
    double latitude;
    double longitude;
    string name; // Optional (station name etc.)
};


struct Edge
{
    int to;
    double distance;    // in km
    double cost_per_km; // cost per km
    double speed;       // km/h
    TransportType type;
    Schedule schedule;
};



class Graph
{   public:
    vector<Node> nodes;
    vector<Edge> edges;

    int addNode(double lat, double lon, const string &name);
    void addEdge(int from, const Edge &edge);
    int findNearestNode(double lat, double lon);
};