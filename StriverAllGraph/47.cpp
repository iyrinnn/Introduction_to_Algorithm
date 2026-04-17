#include <bits/stdc++.h>
using namespace std;

class DisjointSet {
    vector<int> parent, size;

    public :
    DisjointSet (int n){
        parent.resize (n+1);
        size.assign(n+1, 1);


    }

    int find(int x){
        if ( parent[x] == x) return x;
        return parent[x] = find(x);
    }

    void unite(int u, int v){
        int pu = find(u);
        int pv = find(v);

        if (pu != pv){
            if(pu < pv) {
                swap (pu, pv);
            }

            parent[v] = u;
            size[u] += size[v];
        }
    }

}