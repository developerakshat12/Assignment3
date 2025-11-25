#include <stdio.h>

#define MAX 10000

int adj[MAX][MAX];   // adjacency list
int deg[MAX];        // degree of each node
int visited[MAX];
int dist[MAX];

int N, A, B;

void dfs(int node, int parent) {
    visited[node] = 1;

    if (node == B) return;  // stop DFS when B is found

    for (int i = 0; i < deg[node]; i++) { // i < N-1 (X) it is deg[node]
        int nxt = adj[node][i];

        if (!visited[nxt]) {
            dist[nxt] = dist[node] + 1;
            dfs(nxt, node);
        }
    }
}

int main() {
    scanf("%d", &N);

    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        //imp u -> v and v -> u
        adj[u][deg[u]++] = v;
        adj[v][deg[v]++] = u;
    }

    scanf("%d %d", &A, &B);

    // initialize
    for (int i = 0; i < N; i++) {
        visited[i] = 0;
        dist[i] = 0;
    }

    // start DFS from A
    dfs(A, -1);

    printf("%d\n", dist[B]);

    return 0;
}
