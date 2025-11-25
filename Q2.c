#include <stdio.h>

#define MAX 100

char grid[MAX][MAX];
int visited[MAX][MAX];
int R, C;

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

int dfs(int x, int y) {
    visited[x][y] = 1;
    int area = 1;  // current cell counts as 1

    for (int k = 0; k < 4; k++) {
        int nx = x + dx[k];
        int ny = y + dy[k];

        if (nx < 0 || ny < 0 || nx >= R || ny >= C)
            continue;

        if (!visited[nx][ny] && grid[nx][ny] == '1')
            area += dfs(nx, ny);
    }

    return area;
}

int main() {
    scanf("%d %d", &R, &C);

    // Read the grid
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            scanf(" %c", &grid[i][j]);   // space before %c ignores whitespace

    int largest = 0;

    // Explore all estates
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {

            if (grid[i][j] == '1' && !visited[i][j]) {
                int area = dfs(i, j);
                if (area > largest)
                    largest = area;
            }
        }
    }

    printf("%d\n", largest);

    return 0;
}
