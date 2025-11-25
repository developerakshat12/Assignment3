#include <stdio.h>
#include <stdlib.h>

#define MAXN 100000    // max nodes (adjust if needed)
#define MAXM 200000    // max edges (adjust if needed)

typedef struct {
    int u, v;
    int w;
} Edge;

Edge edges[MAXM];
int parent[MAXN];
int rankv[MAXN];

int findp(int x) {
    if (parent[x] == x) return x;
    parent[x] = findp(parent[x]); // path compression
    return parent[x];
}

void unite(int a, int b) {
    a = findp(a); b = findp(b);
    if (a == b) return;
    if (rankv[a] < rankv[b]) parent[a] = b;
    else if (rankv[b] < rankv[a]) parent[b] = a;
    else { parent[b] = a; rankv[a]++; }
}

int cmp_edges(const void *pa, const void *pb) {
    Edge *a = (Edge*)pa;
    Edge *b = (Edge*)pb;
    if (a->w < b->w) return -1;
    if (a->w > b->w) return 1;
    return 0;
}

int main() {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) return 0;

    for (int i = 0; i < M; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        edges[i].u = u;
        edges[i].v = v;
        edges[i].w = w;
    }

    // init DSU
    for (int i = 0; i < N; i++) {
        parent[i] = i;
        rankv[i] = 0;
    }

    // sort edges by weight increasing
    qsort(edges, M, sizeof(Edge), cmp_edges);

    int used = 0;
    int maxEdgeUsed = -1;

    for (int i = 0; i < M && used < N - 1; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].w;
        if (findp(u) != findp(v)) {
            unite(u, v);
            used++;
            if (w > maxEdgeUsed) maxEdgeUsed = w;
        }
    }

    // If we used fewer than N-1 edges, graph was disconnected
    if (used < N - 1) {
        printf("-1\n"); // or print some error value; MST not possible
    } else {
        printf("%d\n", maxEdgeUsed);
    }

    return 0;
}
