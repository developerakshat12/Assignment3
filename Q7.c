#include <stdio.h>
#include <stdlib.h>

#define MAX 10000

int adj[MAX][MAX];         // adjacency matrix (simple for beginners)
int visited[MAX];
int queue[MAX];
int front = 0, rear = 0;

void enqueue(int x) { queue[rear++] = x; }
int dequeue() { return queue[front++]; }
int isEmpty() { return front == rear; }

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    // build graph
    for(int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u][v] = adj[v][u] = 1;
    }

    int S;
    scanf("%d", &S);

    visited[S] = 1;

    // BFS
    enqueue(S);

    int largestTier = 0;

    while(!isEmpty()) {
        int levelCount = rear - front;  // nodes in current tier
        if(levelCount == 0) break;

        // but skip Tier 0 size calculation
        int actualCount = 0;
        for(int i = 0; i < levelCount; i++) {
            int node = dequeue();

            // explore neighbors
            for(int j = 0; j < N; j++) {
                if(adj[node][j] && !visited[j]) {
                    visited[j] = 1;
                    enqueue(j);
                    actualCount++;
                }
            }
        }

        if(actualCount > largestTier)
            largestTier = actualCount;
    }

    printf("%d", largestTier);
    return 0;
}
