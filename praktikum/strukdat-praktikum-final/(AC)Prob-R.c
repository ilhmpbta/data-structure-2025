#include <stdio.h>
#define MAX 1000

int wasd[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int dfs(char grid[MAX][MAX], int visited[MAX][MAX], int H, int W, int x, int y) {
    int size = 1;
    visited[x][y] = 1; 
    for (int i = 0; i < 4; i++) {
        int nx = x + wasd[i][0];
        int ny = y + wasd[i][1];
        if (nx >= 0 && nx < H && ny >= 0 && ny < W && grid[nx][ny] == '+' && !visited[nx][ny]) size += dfs(grid, visited, H, W, nx, ny);
    } return size;
}

void cse_count(int H, int W, char grid[MAX][MAX]) {
    int visited[MAX][MAX] = {0};
    int C = 0, S = 0, E = 0;

    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (grid[i][j] == '+' && !visited[i][j]) {
                C++;
                int colony_size = dfs(grid, visited, H, W, i, j); 
                if (colony_size > S)  S = colony_size;
                if (colony_size % 2 == 0) E++;
            }
        }
    } printf("%d %d %d\n", C, S, E);
}

int main() {
    int H, W; scanf("%d %d", &H, &W);
    char grid[MAX][MAX];

    for (int i = 0; i < H; i++) scanf("%s", grid[i]);
    cse_count(H, W, grid);
    return 0;
}
