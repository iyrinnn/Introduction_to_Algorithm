#include <bits/stdc++.h>
using namespace std;

int main()
{
    int caseNo = 1;
    while (true)
    {
        vector<vector<int>> dist(100, vector<int>(100, 1e9));
        int maxNode = 0;
        while (true)
        {
            int a, b;
            cin >> a >> b;
            if (a == 0 && b == 0)
                break;
            a--;
            b--;
            dist[a][b] = 1;
            maxNode = max(maxNode, max(a, b));
        }
        if (maxNode == 0)
            break;

        for (int i = 0; i <= maxNode; i++)
            dist[i][i] = 0;

        for (int k = 0; k <= maxNode; k++)
        {
            for (int i = 0; i <= maxNode; i++)
            {
                for (int j = 0; j <= maxNode; j++)
                {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }

        double sum = 0;
        int count = 0;
        for (int i = 0; i <= maxNode; i++)
        {
            for (int j = 0; j <= maxNode; j++)
            {
                if (i != j)
                {
                    sum += dist[i][j];
                    count++;
                }
            }
        }

        double avg = sum / count;
        cout << "Case " << caseNo++ << ": average length between pages = ";
        cout << fixed << setprecision(3) << avg << " clicks" << endl;
    }
    return 0;
}
