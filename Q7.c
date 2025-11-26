#include <stdio.h>

#define MAX 1000

int adj[MAX][MAX];
int visited[MAX];
int queue[MAX];

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    // Build adjacency matrix
    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u][v] = 1;
        adj[v][u] = 1;
    }

    int S;
    scanf("%d", &S);

    // BFS queue
    int front = 0, rear = 0;

    visited[S] = 1;
    queue[rear++] = S;

    int largestTier = 0;

    while (front < rear) {

        int levelSize = rear - front;   // nodes in this tier
        int nextTierCount = 0;          // nodes in next tier

        // Process current tier
        for (int i = 0; i < levelSize; i++) {
            int node = queue[front++];

            // Explore neighbors
            for (int j = 0; j < N; j++) {
                if (adj[node][j] == 1 && !visited[j]) {
                    visited[j] = 1;
                    queue[rear++] = j;
                    nextTierCount++;
                }
            }
        }

        // Skip Tier 0 (levelSize = 1 at start)
        if (nextTierCount > largestTier) {
            largestTier = nextTierCount;
        }
    }

    printf("%d\n", largestTier);
    return 0;
}
