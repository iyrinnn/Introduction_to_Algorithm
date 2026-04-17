#include <bits/stdc++.h>
using namespace std;

enum Mode
{
    CAR = 0,
    METRO = 1,
    BIKALPA_BUS = 2,
    UTTARA_BUS = 3,
    WALK = 4
};

struct Point
{
    double lat, lng;
    string name;
    Point(double l = 0, double t = 0, string n = "") : lat(t), lng(l), name(n) {}
};

struct Edge
{
    int to;
    double dist;
    int mode;
    double speed;     
    double startHour; 
    double endHour;   // Schedule end (11 PM)
    double interval;  // Minutes between departures (15 min)

    Edge(int t, double d, int m, double sp, double sh, double eh, double iv)
        : to(t), dist(d), mode(m), speed(sp), startHour(sh), endHour(eh), interval(iv) {}
};

struct PathStep
{
    int node;
    int mode;
    double dist;
    double travelTime;
    double waitTime;
    double departureTime;
    double arrivalTime;
    string nodeName;
};

struct PathResult
{
    vector<int> path;
    vector<PathStep> steps;
    double totalTime;
    bool found;
};

// Global variables
vector<Point> nodes;
vector<vector<Edge>> graph;
map<pair<double, double>, int> nodeIndex;

// Haversine distance
double haversine(double lat1, double lon1, double lat2, double lon2)
{
    double R = 6371; // Earth's radius in km
    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLon = (lon2 - lon1) * M_PI / 180.0;
    double a = sin(dLat / 2) * sin(dLat / 2) +
               cos(lat1 * M_PI / 180.0) * cos(lat2 * M_PI / 180.0) *
                   sin(dLon / 2) * sin(dLon / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    return R * c;
}

// Safe string to double conversion to avoid stod exceptions
bool safeStod(const string &str, double &result)
{
    if (str.empty())
        return false;
    try
    {
        result = stod(str);
        return true;
    }
    catch (...)
    {
        return false;
    }
}

// Add node
int addNode(double lat, double lng, string name = "")
{
    auto key = make_pair(lat, lng);
    if (nodeIndex.count(key))
        return nodeIndex[key];

    int id = nodes.size();
    nodes.push_back(Point(lng, lat, name));
    graph.push_back({});
    nodeIndex[key] = id;
    return id;
}

// Add edge with all parameters
void addEdge(int from, int to, double dist, int mode, double speed,
             double startHour, double endHour, double interval)
{
    graph[from].push_back(Edge(to, dist, mode, speed, startHour, endHour, interval));
}

// Read CSV
vector<vector<string>> readCSV(string filename)
{
    vector<vector<string>> data;
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "Warning: Cannot open " << filename << endl;
        return data;
    }

    string line;
    while (getline(file, line))
    {
        vector<string> row;
        stringstream ss(line);
        string cell;
        while (getline(ss, cell, ','))
        {
            cell.erase(0, cell.find_first_not_of(" \t\r\n"));
            cell.erase(cell.find_last_not_of(" \t\r\n") + 1);
            row.push_back(cell);
        }
        data.push_back(row);
    }
    return data;
}

// Load roads (10 km/h, always available)
void loadRoads(string filename)
{
    auto data = readCSV(filename);
    int roadCount = 0;

    for (size_t r = 0; r < data.size(); r++)
    {
        auto &row = data[r];
        if (row.size() < 3 || row[0] != "DhakaStreet")
            continue;

        vector<int> pathNodes;
        for (size_t i = 1; i + 1 < row.size(); i += 2)
        {
            double lng, lat;
            if (!safeStod(row[i], lng) || !safeStod(row[i + 1], lat))
                continue;
            pathNodes.push_back(addNode(lat, lng));
        }

        for (size_t i = 0; i + 1 < pathNodes.size(); i++)
        {
            double dist = haversine(nodes[pathNodes[i]].lat, nodes[pathNodes[i]].lng,
                                    nodes[pathNodes[i + 1]].lat, nodes[pathNodes[i + 1]].lng);
            // Car: 10 km/h, always available (0-24)
            addEdge(pathNodes[i], pathNodes[i + 1], dist, CAR, 10.0, 0, 24, 0);
            addEdge(pathNodes[i + 1], pathNodes[i], dist, CAR, 10.0, 0, 24, 0);
            roadCount++;
        }
    }
    cout << "Loaded " << roadCount << " road segments\n";
}

// Load metro (10 km/h, every 15 min, 6 AM - 11 PM)
void loadMetro(string filename)
{
    auto data = readCSV(filename);
    int metroCount = 0;

    for (size_t r = 0; r < data.size(); r++)
    {
        auto &row = data[r];
        if (row.size() < 3)
            continue;

        vector<int> pathNodes;
        for (size_t i = 1; i + 1 < row.size(); i += 2)
        {
            double lng, lat;
            if (!safeStod(row[i], lng) || !safeStod(row[i + 1], lat))
                continue;
            pathNodes.push_back(addNode(lat, lng));
        }

        for (size_t i = 0; i + 1 < pathNodes.size(); i++)
        {
            double dist = haversine(nodes[pathNodes[i]].lat, nodes[pathNodes[i]].lng,
                                    nodes[pathNodes[i + 1]].lat, nodes[pathNodes[i + 1]].lng);
            // Metro: 10 km/h, every 15 min, 6 AM - 11 PM
            addEdge(pathNodes[i], pathNodes[i + 1], dist, METRO, 10.0, 6, 23, 15);
            metroCount++;
        }
    }
    cout << "Loaded " << metroCount << " metro segments\n";
}

// Load Buses (10 km/h, every 15 min, 6 AM - 11 PM)
void loadBus(string filename, int mode)
{
    auto data = readCSV(filename);
    int busCount = 0;

    for (size_t r = 0; r < data.size(); r++)
    {
        auto &row = data[r];
        if (row.size() < 3)
            continue;

        vector<int> pathNodes;
        for (size_t i = 1; i + 1 < row.size(); i += 2)
        {
            double lng, lat;
            if (!safeStod(row[i], lng) || !safeStod(row[i + 1], lat))
                continue;
            pathNodes.push_back(addNode(lat, lng));
        }

        for (size_t i = 0; i + 1 < pathNodes.size(); i++)
        {
            double dist = haversine(nodes[pathNodes[i]].lat, nodes[pathNodes[i]].lng,
                                    nodes[pathNodes[i + 1]].lat, nodes[pathNodes[i + 1]].lng);
            // Bus: 10 km/h, every 15 min, 6 AM - 11 PM
            addEdge(pathNodes[i], pathNodes[i + 1], dist, mode, 10.0, 6, 23, 15);
            busCount++;
        }
    }
    cout << "Loaded " << busCount << " bus segments for mode " << mode << "\n";
}

// Find nearest node
int findNearestNode(double lat, double lng)
{
    int best = -1;
    double minDist = 1e9;
    for (size_t i = 0; i < nodes.size(); i++)
    {
        double dist = haversine(lat, lng, nodes[i].lat, nodes[i].lng);
        if (dist < minDist)
        {
            minDist = dist;
            best = i;
        }
    }
    return best;
}

// Prepare location (handle three cases from Section 3)
int prepareLocation(double lat, double lng, bool isSource)
{
    int nearest = findNearestNode(lat, lng);
    if (nearest == -1)
        return -1;

    double dist = haversine(lat, lng, nodes[nearest].lat, nodes[nearest].lng);

    // Case A: On node (within 50m)
    if (dist < 0.05)
    {
        return nearest;
    }

    // Case B or C: Add temporary node
    string name = isSource ? "Source" : "Destination";
    int temp = addNode(lat, lng, name);

    // Case B: On road (<= 0.5km) - use car
    // Case C: Off road (> 0.5km) - use walk at 2 km/h
    int mode = (dist > 0.5) ? WALK : CAR;
    double speed = (mode == WALK) ? 2.0 : 10.0;

    addEdge(temp, nearest, dist, mode, speed, 0, 24, 0);
    addEdge(nearest, temp, dist, mode, speed, 0, 24, 0);

    return temp;
}

// Format time (e.g., 18.75 -> "6:45 PM")
string formatTime(double hours)
{
    int totalMins = round(hours * 60);
    int h = totalMins / 60;
    int m = totalMins % 60;
    string ampm = (h < 12) ? "AM" : "PM";
    int displayHour = h % 12;
    if (displayHour == 0)
        displayHour = 12;

    stringstream ss;
    ss << displayHour << ":" << setfill('0') << setw(2) << m << " " << ampm;
    return ss.str();
}

// Parse time string to hours (e.g., "5:43 PM" -> 17.7167)
double parseTime(string timeStr)
{
    int hour, minute;
    string ampm;
    char colon;

    stringstream ss(timeStr);
    ss >> hour >> colon >> minute >> ampm;

    if (ampm == "PM" && hour != 12)
        hour += 12;
    if (ampm == "AM" && hour == 12)
        hour = 0;

    return hour + minute / 60.0;
}

// Get mode name
string modeName(int mode)
{
    switch (mode)
    {
    case CAR:
        return "Car";
    case METRO:
        return "Metro";
    case BIKALPA_BUS:
        return "Bikalpa Bus";
    case UTTARA_BUS:
        return "Uttara Bus";
    case WALK:
        return "Walk";
    default:
        return "Unknown";
    }
}

// Calculate next departure time for scheduled services
double getNextDeparture(double currentTime, double startHour, double endHour, double intervalMin)
{
    if (intervalMin <= 0)
        return currentTime; // No schedule (car/walk)

    // Before service starts
    if (currentTime < startHour)
        return startHour;

    // After service ends
    if (currentTime >= endHour)
        return -1;

    // Find next departure
    double interval = intervalMin / 60.0;
    double timeSinceStart = currentTime - startHour;
    double nextDeparture = startHour + ceil(timeSinceStart / interval) * interval;

    return (nextDeparture < endHour) ? nextDeparture : -1;
}

// Find fastest path (minimize time)
PathResult findFastestPath(int start, int end, double startTime)
{
    PathResult result;
    result.found = false;
    result.totalTime = 1e9;

    int n = nodes.size();
    vector<double> time(n, 1e9);        // Total journey time so far
    vector<double> arrivalTime(n, 1e9); // Actual clock time at node
    vector<int> parent(n, -1);
    vector<int> parentMode(n, -1);
    vector<double> parentDist(n, 0);
    vector<double> parentWait(n, 0);
    vector<bool> visited(n, false);

    time[start] = 0;
    arrivalTime[start] = startTime;

    for (int i = 0; i < n; i++)
    {
        // Find unvisited node with minimum time
        int u = -1;
        for (int j = 0; j < n; j++)
        {
            if (!visited[j] && (u == -1 || time[j] < time[u]))
            {
                u = j;
            }
        }

        if (u == -1 || time[u] > 1e8)
            break;
        visited[u] = true;

        double currentTime = arrivalTime[u];

        // Try all edges from u
        for (size_t e = 0; e < graph[u].size(); e++)
        {
            Edge &edge = graph[u][e];

            // Calculate waiting time for scheduled services
            double waitTime = 0;
            double departureTime = currentTime;

            if (edge.interval > 0)
            {
                double nextDep = getNextDeparture(currentTime, edge.startHour, edge.endHour, edge.interval);
                if (nextDep < 0)
                    continue; // No service available
                waitTime = nextDep - currentTime;
                departureTime = nextDep;
            }

            // Calculate travel time and arrival
            double travelTime = edge.dist / edge.speed;
            double newArrival = departureTime + travelTime;
            double totalJourneyTime = time[u] + waitTime + travelTime;

            // Update if faster path found
            if (totalJourneyTime < time[edge.to])
            {
                time[edge.to] = totalJourneyTime;
                arrivalTime[edge.to] = newArrival;
                parent[edge.to] = u;
                parentMode[edge.to] = edge.mode;
                parentDist[edge.to] = edge.dist;
                parentWait[edge.to] = waitTime;
            }
        }
    }

    if (time[end] >= 1e8)
    {
        return result;
    }

    result.found = true;
    result.totalTime = time[end];

    
    vector<int> path;
    int curr = end;
    while (curr != -1)
    {
        path.push_back(curr);
        curr = parent[curr];
    }
    reverse(path.begin(), path.end());
    result.path = path;

    vector<PathStep> steps;
    double current = startTime;

    for (size_t i = 1; i < path.size(); i++)
    {
        int from = path[i - 1];
        int to = path[i];
        int mode = parentMode[to];
        double dist = parentDist[to];
        double wait = parentWait[to];

        
        double speed = 10.0;

        PathStep step;
        step.node = to;
        step.mode = mode;
        step.dist = dist;
        step.travelTime = dist / speed;
        step.waitTime = wait;
        step.departureTime = current + wait;
        step.arrivalTime = step.departureTime + step.travelTime;
        step.nodeName = nodes[to].name;

        steps.push_back(step);
        current = step.arrivalTime;
    }

    result.steps = steps;

    return result;
}

// Write KML file
void writeKML(vector<int> &path, string filename, int caseNum)
{
    ofstream file(filename);
    if (!file.is_open())
    {
        cout << "Error: Cannot create KML file " << filename << endl;
        return;
    }

    file << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
    file << "<kml xmlns=\"http://earth.google.com/kml/2.1\">\n";
    file << "<Document>\n";
    file << "<Placemark>\n";
    file << "<name>Route P5 Case " << caseNum << "</name>\n";
    file << "<LineString>\n";
    file << "<tessellate>1</tessellate>\n";
    file << "<coordinates>\n";

    for (size_t i = 0; i < path.size(); i++)
    {
        int id = path[i];
        file << fixed << setprecision(6) << nodes[id].lng << "," << nodes[id].lat << ",0\n";
    }

    file << "</coordinates>\n";
    file << "</LineString>\n";
    file << "</Placemark>\n";
    file << "</Document>\n";
    file << "</kml>\n";
    file.close();
}

int main()
{
    cout << "\n==========================================\n";
    cout << "PROBLEM 5: Fastest Route (Minimize Time)\n";
    cout << "==========================================\n\n";

    cout << "VEHICLE SPECIFICATIONS:\n";
    cout << "----------------------\n";
    cout << "All vehicles: 10 km/h\n";
    cout << "Metro & Buses: Every 15 minutes (6 AM - 11 PM)\n";
    cout << "Car: Always available\n";
    cout << "Walk: 2 km/h (For off-road locations)\n\n";

    // Load all data
    cout << "Loading datasets...\n";
    cout << "--------------------\n";
    loadRoads("../datasets/Roadmap-Dhaka.csv");
    loadMetro("../datasets/Routemap-DhakaMetroRail.csv");
    loadBus("../datasets/Routemap-BikolpoBus.csv", BIKALPA_BUS);
    loadBus("../datasets/Routemap-UttaraBus.csv", UTTARA_BUS);

    cout << "\nTotal locations loaded: " << nodes.size() << "\n\n";

    // Get user input for start time
    string startTimeStr;

    cout << "Enter start time (e.g., 5:43 PM): ";
    getline(cin, startTimeStr);

    double startTime = parseTime(startTimeStr);

    cout << "\nStart Time: " << formatTime(startTime) << "\n\n";

    // Read test cases
    ifstream input("../input.txt");
    if (!input.is_open())
    {
        cout << "Error: Cannot open input.txt\n";
        cout << "Please make sure input.txt exists in the root folder\n";
        return 1;
    }

    string line;
    int caseNum = 1;
    int successCount = 0;

    while (getline(input, line))
    {
        stringstream ss(line);
        double slng, slat, dlng, dlat;
        ss >> slng >> slat >> dlng >> dlat;

        cout << "\n"
             << string(50, '-') << "\n";
        cout << "CASE " << caseNum << "\n";
        cout << string(50, '-') << "\n";

        // Prepare locations (handles all three cases from Section 3)
        int src = prepareLocation(slat, slng, true);
        int dst = prepareLocation(dlat, dlng, false);

        if (src == -1 || dst == -1)
        {
            cout << "ERROR: Cannot find nearby nodes for source or destination\n";
            caseNum++;
            continue;
        }

        // Find fastest path
        PathResult result = findFastestPath(src, dst, startTime);

        if (!result.found)
        {
            cout << "RESULT: No path found\n";
            caseNum++;
            continue;
        }

        successCount++;

        // Print problem header
        cout << "Problem No: 5\n";
        cout << "Source: (" << fixed << setprecision(6) << slng << ", " << slat << ")\n";
        cout << "Destination: (" << dlng << ", " << dlat << ")\n";
        cout << "Starting time: " << formatTime(startTime) << "\n";
        cout << "Destination reaching time: " << formatTime(result.steps.back().arrivalTime) << "\n\n";

        // Print route description
        cout << "ROUTE DESCRIPTION:\n";
        cout << "------------------\n";

        for (size_t i = 0; i < result.steps.size(); i++)
        {
            // Print waiting period if any
            if (result.steps[i].waitTime > 0.001)
            {
                double waitStart = result.steps[i].departureTime - result.steps[i].waitTime;
                cout << formatTime(waitStart) << " - " << formatTime(result.steps[i].departureTime);
                cout << ", Wait at ";

                int fromNode = (i == 0) ? src : result.steps[i - 1].node;
                if (!nodes[fromNode].name.empty())
                    cout << nodes[fromNode].name;
                else
                    cout << "(" << fixed << setprecision(6) << nodes[fromNode].lng
                         << ", " << nodes[fromNode].lat << ")";
                cout << " for " << modeName(result.steps[i].mode) << ".\n";
            }

            // Print travel segment
            cout << formatTime(result.steps[i].departureTime) << " - " << formatTime(result.steps[i].arrivalTime);
            cout << ": Ride " << modeName(result.steps[i].mode) << " from ";

            int fromNode = (i == 0) ? src : result.steps[i - 1].node;
            if (!nodes[fromNode].name.empty())
                cout << nodes[fromNode].name;
            else
                cout << "(" << nodes[fromNode].lng << ", " << nodes[fromNode].lat << ")";

            cout << " to ";

            if (!result.steps[i].nodeName.empty())
                cout << result.steps[i].nodeName;
            else
                cout << "(" << nodes[result.steps[i].node].lng << ", " << nodes[result.steps[i].node].lat << ")";

            cout << ".\n";
        }

        cout << "\nSUMMARY:\n";
        cout << "--------\n";
        cout << "Total Time: " << fixed << setprecision(1) << (result.totalTime * 60) << " minutes\n";
        cout << "Arrival: " << formatTime(result.steps.back().arrivalTime) << "\n";

        // Save KML
        string kmlFile = "../output/route_p5_case" + to_string(caseNum) + ".kml";
        writeKML(result.path, kmlFile, caseNum);
        cout << "\nKML file saved to: " << kmlFile << "\n";

        caseNum++;
    }

    input.close();

    cout << "\n"
         << string(50, '=') << "\n";
    cout << "SUMMARY: " << successCount << " out of " << (caseNum - 1) << " cases successful\n";
    cout << string(50, '=') << "\n";

    return 0;
}