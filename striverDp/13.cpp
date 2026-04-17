#include <bits/stdc++.h>
using namespace std;

int f(int i, int j1, int j2, int r, int c,
      vector<vector<int>> &grid,
      vector<vector<vector<int>>> &dp)
{

    // Out of bounds
    if (j1 < 0 || j2 < 0 || j1 >= c || j2 >= c)
        return -1e8;

    // Last row
    if (i == r - 1)
    {
        if (j1 == j2)
            return grid[i][j1];
        else
            return grid[i][j1] + grid[i][j2];
    }

    // Memoization
    if (dp[i][j1][j2] != -1)
        return dp[i][j1][j2];

    int maxi = -1e8;

    // Try all 9 moves
    for (int dj1 = -1; dj1 <= 1; dj1++)
    {
        for (int dj2 = -1; dj2 <= 1; dj2++)
        {

            int value = 0;
            if (j1 == j2)
                value = grid[i][j1];
            else
                value = grid[i][j1] + grid[i][j2];

            value += f(i + 1, j1 + dj1, j2 + dj2, r, c, grid, dp);
            maxi = max(maxi, value);
        }
    }

    return dp[i][j1][j2] = maxi;
}

int maximumChocolates(int r, int c, vector<vector<int>> &grid)
{
    vector<vector<vector<int>>> dp(
        r, vector<vector<int>>(c, vector<int>(c, -1)));

    return f(0, 0, c - 1, r, c, grid, dp);
}

int main()
{
    int r, c;
    cin >> r >> c;

    vector<vector<int>> grid(r, vector<int>(c));
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            cin >> grid[i][j];
        }
    }

    cout << maximumChocolates(r, c, grid);
    return 0;
}

#include <bits/stdc++.h>
using namespace std;

int maximumChocolates(int n, int m, vector<vector<int>> &grid)
{

    // dp[i][j1][j2] = max chocolates from row i when
    // Alice at j1 and Bob at j2
    vector<vector<vector<int>>> dp(
        n, vector<vector<int>>(m, vector<int>(m, -1e8)));

    // Base case: last row
    for (int j1 = 0; j1 < m; j1++)
    {
        for (int j2 = 0; j2 < m; j2++)
        {
            if (j1 == j2)
                dp[n - 1][j1][j2] = grid[n - 1][j1];
            else
                dp[n - 1][j1][j2] = grid[n - 1][j1] + grid[n - 1][j2];
        }
    }

    // Fill table from bottom to top
    for (int i = n - 2; i >= 0; i--)
    {
        for (int j1 = 0; j1 < m; j1++)
        {
            for (int j2 = 0; j2 < m; j2++)
            {

                int maxi = -1e8;

                for (int dj1 = -1; dj1 <= 1; dj1++)
                {
                    for (int dj2 = -1; dj2 <= 1; dj2++)
                    {

                        int nj1 = j1 + dj1;
                        int nj2 = j2 + dj2;

                        if (nj1 >= 0 && nj1 < m && nj2 >= 0 && nj2 < m)
                        {

                            int value;
                            if (j1 == j2)
                                value = grid[i][j1];
                            else
                                value = grid[i][j1] + grid[i][j2];

                            value += dp[i + 1][nj1][nj2];
                            maxi = max(maxi, value);
                        }
                    }
                }

                dp[i][j1][j2] = maxi;
            }
        }
    }

    // Alice starts at (0,0), Bob at (0,m-1)
    return dp[0][0][m - 1];
}

int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<int>> grid(n, vector<int>(m));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> grid[i][j];
        }
    }

    cout << maximumChocolates(n, m, grid);
    return 0;
}
