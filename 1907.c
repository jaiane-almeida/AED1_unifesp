//usando BFS cm fila estatica meu Deus eu nao aguento maissss
//coloração de cenários de jogos 

#include <stdio.h>

#define MAX 1024

char grid[MAX][MAX];
int visited[MAX][MAX];
int N, M;

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

typedef struct {
    int x, y;
} Node;

Node queue[MAX * MAX];

void bfs(int sx, int sy) {
    int front = 0, back = 0;
    queue[back++] = (Node){sx, sy};
    visited[sx][sy] = 1;

    while (front < back) {
        Node u = queue[front++];

        for (int k = 0; k < 4; k++) {
            int nx = u.x + dx[k];
            int ny = u.y + dy[k];

            if (nx >= 0 && nx < N && ny >= 0 && ny < M) {
                if (!visited[nx][ny] && grid[nx][ny] == '.') {
                    visited[nx][ny] = 1;
                    queue[back++] = (Node){nx, ny};
                }
            }
        }
    }
}

int main() {
    scanf("%d %d", &N, &M);

    for (int i = 0; i < N; i++) {
        scanf("%s", grid[i]);
    }

    int clicks = 0;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (!visited[i][j] && grid[i][j] == '.') {
                bfs(i, j);
                clicks++;
            }
        }
    }

    printf("%d\n", clicks);
    return 0;
}
