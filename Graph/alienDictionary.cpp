#include <bits/stdc++.h>
using namespace std;

void dfs(int curr, vector<int> adj[], vector<bool> &vis, stack<int> &s) // O(V + E)
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

void topologicalSort(int v, vector<int> adj[], vector<int> &toposort)
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

    while (!s.empty())
    {
        toposort.push_back(s.top());
        s.pop();
    }
}

// Here they have stated ordering is possible
string findOrder(string dic[], int n, int k)
{
    vector<int> adj[k];

    for (int i = 0; i < n - 1; i++) // n-1 because we need pairs
    {
        string s1 = dic[i];
        string s2 = dic[i + 1];
        int len = min(s1.size(), s2.size());

        for (int ptr = 0; ptr < len; ptr++)
        {
            if (s1[ptr] != s2[ptr])
            {
                adj[s1[ptr] - 'a'].push_back(s2[ptr] - 'a');
                break;
            }
        }
    }

    vector<int> toposort;
    topologicalSort(k, adj, toposort);

    string ans = "";
    for (auto it : toposort)
    {
        ans += char(it + 'a');
    }

    return ans;
}

/*
    When will the order be NOT possible:
    Case 1: If a larger string comes before a smaller one like "abcd" before "abc"
    Case 2: If there are cyclic dependencies (e.g., a -> b -> c -> a)
*/

int main()
{
    // Example test case from GeeksForGeeks
    string dict[] = {"baa", "abcd", "abca", "cab", "cad"};
    int N = 5, K = 4;

    string order = findOrder(dict, N, K);
    cout << "The order of characters in the alien language is: " << order << endl;

    return 0;
}
