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

        // boundaries
        if (nx < 0 || ny < 0 || nx >= R || ny >= C)
            continue;

        // cannot go through walls
        if (grid[nx][ny] == 'X')
            continue;

        int newDist = dist[x][y] + 1;

        // prune: only continue if this DFS gives a **better** time
        if (dist[nx][ny] == -1 || newDist < dist[nx][ny]) {
            dist[nx][ny] = newDist;
            dfs(nx, ny);
        }
    }
}

int main() {
    scanf("%d %d", &R, &C);

    // read grid
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            scanf(" %c", &grid[i][j]);

    // init dist
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            dist[i][j] = -1;

    // Start DFS from every Z (multi-source DFS)
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (grid[i][j] == 'Z') {
                dist[i][j] = 0;
                dfs(i, j);
            }
        }
    }

    // Convert infected humans and find max infection time
    int lastTime = -1;

    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {

            if (grid[i][j] == 'H' && dist[i][j] != -1) {
                grid[i][j] = 'Z';          // becomes a zombie
                if (dist[i][j] > lastTime)
                    lastTime = dist[i][j];
            }

        }
    }

    // Output grid
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            printf("%c", grid[i][j]);
            if (j + 1 < C) printf(" ");
        }
        printf("\n");
    }

    // Output time
    if (lastTime == -1) printf("0\n");
    else printf("%d\n", lastTime);

    return 0;
}
