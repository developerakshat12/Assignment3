#include <stdio.h>

#define MAX 100

char grid[MAX][MAX];
int dist[MAX][MAX];
int R, C;

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

void dfs(int x, int y) {
    for (int k = 0; k < 4; k++) {
        int nx = x + dx[k];
        int ny = y + dy[k];

        // out of bounds
        if (nx < 0 || ny < 0 || nx >= R || ny >= C)
            continue;

        // only spread to 'O'
        if (grid[nx][ny] != 'O')
            continue;

        // if not visited OR shorter time found
        if (dist[nx][ny] == -1 || dist[nx][ny] > dist[x][y] + 1) {
            dist[nx][ny] = dist[x][y] + 1;
            dfs(nx, ny);
        }
    }
}

int main() {
    scanf("%d %d", &R, &C);

    int sx = -1, sy = -1;

    // read grid
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            scanf(" %c", &grid[i][j]);
            if (grid[i][j] == 'S') {
                sx = i;
                sy = j;
            }
        }
    }

    // initialize distances
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            dist[i][j] = -1;

    // starting point
    dist[sx][sy] = 0;

    // run DFS
    dfs(sx, sy);

    // find max time
    int maxTime = -1;

    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (grid[i][j] == 'O' && dist[i][j] != -1) {
                if (dist[i][j] > maxTime)
                    maxTime = dist[i][j];
            }
        }
    }

    // print answer
    if (maxTime == -1)
        printf("0\n");
    else
        printf("%d\n", maxTime);

    return 0;
}
