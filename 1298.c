#include <stdio.h>

#define N 300

const int dx[4] = {0, 1, 0, -1};
const int dy[4] = {1, 0, -1, 0};

int n;
char g[4*N + 5][4*N + 5];

int ROWS, COLUMNS;

// BFS manual
void bfs(int sx, int sy) {
    static int qx[4*N*4*N];
    static int qy[4*N*4*N];

    int front = 0, back = 0;

    qx[back] = sx;
    qy[back] = sy;
    back++;

    g[sx][sy] = 1;

    while (front < back) {
        int x = qx[front];
        int y = qy[front];
        front++;

        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d];
            int ny = y + dy[d];

            if (nx >= 0 && nx < ROWS &&
                ny >= 0 && ny < COLUMNS &&
                g[nx][ny] == 0)
            {
                g[nx][ny] = 1;
                qx[back] = nx;
                qy[back] = ny;
                back++;
            }
        }
    }
}

int main() {
    while (scanf("%d", &n) == 1) {

        ROWS = 4 * n;
        COLUMNS = 2 * (2*n + 1);

        // Reset grid
        for (int i = 0; i < ROWS; i++)
            for (int j = 0; j < COLUMNS; j++)
                g[i][j] = 0;

        int evenLine, bi, bj;
        char b;

        for (int i = 0; i < 2*n - 1; i++) {
            for (int j = 0; j < n; j++) {
                do { b = getchar(); } while (b == ' ' || b == '\n');

                evenLine = i % 2;
                bi = 2*i + 1;
                bj = 2*(2*j + evenLine) + 1;

                if (b == 'H') {
                    g[bi][bj-1] = 1;
                    g[bi][bj] = 1;
                    g[bi][bj+1] = 1;
                    g[bi][bj+2] = 1;
                } else { // 'V'
                    g[bi-1][bj] = 1;
                    g[bi][bj] = 1;
                    g[bi+1][bj] = 1;
                    g[bi+2][bj] = 1;
                }
            }
        }

        int cfcs = 0;

        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLUMNS; j++) {
                if (g[i][j] == 0) {
                    bfs(i, j);
                    cfcs++;
                }
            }
        }

        printf("%d\n", cfcs - 1);
    }

    return 0;
}
