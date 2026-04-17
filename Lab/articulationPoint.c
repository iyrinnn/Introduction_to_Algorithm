#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 100
#define WHITE 0
#define GRAY 1
#define BLACK 2
#define INF 9999


typedef struct {
    int V;
    int Adj[MAX][MAX];
} Graph;

// Global arrays
int color[MAX], d[MAX], f[MAX], parent[MAX], low[MAX], articulation[MAX];
int time = 0;


void DFS_VISIT(Graph G, int u) {
    color[u] = GRAY;
    d[u] = low[u] = ++time;

    int children = 0;  

    for (int v = 0; v < G.V; v++) {
        if (G.Adj[u][v]) {      // Edge exists

            if (color[v] == WHITE) {
                parent[v] = u;
                children++;

                DFS_VISIT(G, v);

                // Low-link update for tree edge
                low[u] = (low[u] < low[v]) ? low[u] : low[v];

                // Articulation point rule (non-root)
                if (parent[u] != -1 && low[v] >= d[u])
                    articulation[u] = 1;

            }
            else if (v != parent[u]) {
                // Back edge
                low[u] = (low[u] < d[v]) ? low[u] : d[v];
            }
        }
    }

    // Root articulation check
    if (parent[u] == -1 && children > 1)
        articulation[u] = 1;

    color[u] = BLACK;
    f[u] = ++time;
}


// DFS(G)
void DFS(Graph G) {
    for (int u = 0; u < G.V; u++) {
        color[u] = WHITE;
        parent[u] = -1;
        low[u] = INT_MAX;
        f[u] = INT_MAX ;
        d[u] = INT_MAX;
    }

    time = 0;

    for (int u = 0; u < G.V; u++) {
        if (color[u] == WHITE) {
            DFS_VISIT(G, u);
        }
    }
}

// MAIN
int main() {
    Graph G;
    int edges, u, v, source;

    printf("Enter number of vertices: ");
    scanf("%d", &G.V);

    // Initialize adjacency matrix
    for (int i = 0; i < G.V; i++)
        for (int j = 0; j < G.V; j++)
            G.Adj[i][j] = 0;

    printf("Enter number of edges: ");
    scanf("%d", &edges);

    printf("Enter edges (from -> to):\n");
    for (int i = 0; i < edges; i++) {
        scanf("%d %d", &u, &v);
        G.Adj[u][v] = 1;
        // For undirected graph, add: G.Adj[v][u] = 1;
    }

   
    printf("\n--- DFS(G) ---\n");
    DFS(G);
    for (int i = 0; i < G.V; i++) {
        printf("Node %d: Discovery = %d, Finish = %d, Parent = %d\n", i, d[i], f[i], parent[i]);
    }

    return 0;
}