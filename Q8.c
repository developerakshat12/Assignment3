#include <stdio.h>
#include <stdlib.h>

#define MAX 10000

int adj[MAX][MAX];      // adjacency list (simple for this problem)
int size[MAX];          // size of adj[u]
int parent[MAX];
int depth[MAX];
int visited[MAX];

int N;

void dfs(int node, int par, int d) {
    visited[node] = 1;
    parent[node] = par;
    depth[node] = d;

    for (int i = 0; i < size[node]; i++) {
        int child = adj[node][i];
        if (!visited[child]) {
            dfs(child, node, d + 1);
        }
    }
}

int main() {
    scanf("%d", &N);

    // build adjacency list
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);

        // since u is parent of v, but we do DFS both ways
        adj[u][size[u]++] = v;
        adj[v][size[v]++] = u;
    }

    int A, B;
    scanf("%d %d", &A, &B);

    // DFS from root (0)
    dfs(0, -1, 0);

    // Check cousin conditions:
    if (depth[A] == depth[B] && parent[A] != parent[B])
        printf("COUSINS\n");
    else
        printf("NOT COUSINS\n");

    return 0;
}
