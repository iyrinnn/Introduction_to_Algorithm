#pragma once
#include <string>
#include <vector>  

#include <iostream>
#include "../include/Graph.h"
#include "../include/Dijkstra.h"


pair<vector<double>, vector<int>> dijkstraDistPath(int start);
vector<double> dijkstraDist(int start);
vector<double> dijkstraCost(int start, vector<int> allowedModes);
vector<double> dijkstraTime(int start);