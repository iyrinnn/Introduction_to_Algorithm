#include <bits/stdc++.h>
using namespace std;

int main()
{
    int caseNo = 1;
    while (true)
    {
        int C, S, Q;
        cin >> C >> S >> Q;
        if (C == 0 && S == 0 && Q == 0)
            break;

        vector<vector<int>> sound(C, vector<int>(C, 1e9));
        for (int i = 0; i < S; i++)
        {
            int u, v, d;
            cin >> u >> v >> d;
            u--;
            v--;
            sound[u][v] = d;
            sound[v][u] = d;
        }

        for (int k = 0; k < C; k++)
        {
            for (int i = 0; i < C; i++)
            {
                for (int j = 0; j < C; j++)
                {
                    sound[i][j] = min(sound[i][j], max(sound[i][k], sound[k][j]));
                }
            }
        }

        cout << "Case #" << caseNo++ << endl;
        for (int i = 0; i < Q; i++)
        {
            int u, v;
            cin >> u >> v;
            u--;
            v--;
            if (sound[u][v] == 1e9)
                cout << "no path" << endl;
            else
                cout << sound[u][v] << endl;
        }
        cout << endl;
    }
}