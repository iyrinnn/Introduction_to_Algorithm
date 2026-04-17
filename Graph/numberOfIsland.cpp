#include <bits/stdc++.h>
using namespace std;

void dfs(int i, int j, vector<vector<bool>> &vis, vector<vector<char>> &grid, int n, int m)
{
    if (i < 0 || j < 0 || i >= n || j >= m || vis[i][j] || grid[i][j] != '1')
    {
        return;
    }
    vis[i][j] = true;
    dfs(i - 1, j, vis, grid, n, m); // top
    dfs(i, j - 1, vis, grid, n, m); // left
    dfs(i + 1, j, vis, grid, n, m); // bottom,
    dfs(i, j + 1, vis, grid, n, m); // right
}

int numIslands(vector<vector<char>> &grid)
{
    int islands = 0;
    int n = grid.size();
    int m = grid[0].size();

    vector<vector<bool>> vis(n, vector<bool>(m, false));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (grid[i][j] == '1' && !vis[i][j])
            {
                dfs(i, j, vis, grid, n, m);
                islands++;
            }
        }
    }

    return islands;
}

int main()
{
    vector<vector<char>> grid = {
        {'1', '1', '0', '0', '0'},
        {'1', '1', '0', '0', '0'},
        {'0', '0', '1', '0', '0'},
        {'0', '0', '0', '1', '1'}};

    cout << "Number of islands: " << numIslands(grid) << endl;

    return 0;
}