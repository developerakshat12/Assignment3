#include <stdio.h>

#define MAX 100000   // adjust as needed

int adj[MAX][MAX];    // adjacency list
int deg[MAX];         // degree of each node
int visited[MAX];
int dist[MAX];
int N;

void resetVisitedDist() {
    for (int i = 0; i < N; i++) {
        visited[i] = 0;
        dist[i] = 0;
    }
}

void dfs(int node) {
    visited[node] = 1;

    for (int i = 0; i < deg[node]; i++) {
        int nxt = adj[node][i];
        if (!visited[nxt]) {
            dist[nxt] = dist[node] + 1;
            dfs(nxt);
        }
    }
}

int main() {
    scanf("%d", &N);

    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);

        adj[u][deg[u]++] = v;
        adj[v][deg[v]++] = u;
    }

    // ---- FIRST DFS from node 0 ----
    resetVisitedDist();
    dfs(0);

    // find farthest node from 0
    int far = 0;
    for (int i = 0; i < N; i++)
        if (dist[i] > dist[far])
            far = i;

    // ---- SECOND DFS from far ----
    resetVisitedDist();
    dfs(far);

    // find farthest node from 'far' to get the diameter
    int diameter = 0;
    for (int i = 0; i < N; i++)
        if (dist[i] > diameter)
            diameter = dist[i];

    printf("%d\n", diameter);

    return 0;
}
