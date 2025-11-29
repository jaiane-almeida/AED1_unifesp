#include <stdio.h>
#include <string.h>

#define MAX 10001

int visited[MAX];
int dist[MAX];

int reverse(int x) {
    int r = 0;
    while (x > 0) {
        r = r * 10 + (x % 10);
        x /= 10;
    }
    return r;
}

int bfs(int A, int B) {
    int queue[MAX];
    int front = 0, back = 0;

    memset(visited, 0, sizeof(visited));

    visited[A] = 1;
    dist[A] = 0;
    queue[back++] = A;

    while (front < back) {
        int cur = queue[front++];

        if (cur == B) return dist[cur];

        // Operação 1: +1
        int nxt = cur + 1;
        if (nxt < MAX && !visited[nxt]) {
            visited[nxt] = 1;
            dist[nxt] = dist[cur] + 1;
            queue[back++] = nxt;
        }

        // Operação 2: inverter
        int rev = reverse(cur);
        if (rev < MAX && !visited[rev]) {
            visited[rev] = 1;
            dist[rev] = dist[cur] + 1;
            queue[back++] = rev;
        }
    }

    return -1; // nunca acontece neste problema
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int A, B;
        scanf("%d %d", &A, &B);
        printf("%d\n", bfs(A, B));
    }

    return 0;
}
