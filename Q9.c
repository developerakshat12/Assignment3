#include <stdio.h>

#define MAX 10000      // adjust if needed

int adj[MAX][MAX];     // adjacency list (simple 2D array)
int size[MAX];         // size[u] = number of children of u

// DFS to calculate subtree size
int dfs(int u) {
    int total = 1; // count the manager itself
    for (int i = 0; i < size[u]; i++) {
        int child = adj[u][i];
        total += dfs(child);
    }
    return total;
}

int main() {
    int N;
    scanf("%d", &N);

    // read N-1 manager-report relations
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);

        adj[u][size[u]++] = v;   // add v as child of u
    }

    int U;
    scanf("%d", &U);

    int result = dfs(U);
    printf("%d\n", result);

    return 0;
}
