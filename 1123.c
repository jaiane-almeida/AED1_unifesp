#include <stdio.h>
#include <stdlib.h>

#define INF 1000000000
#define MAX 250

typedef struct {
    int v, w;
    struct Node *next;
} Node;

Node *adj[MAX];
int dist[MAX];
int used[MAX];

void addEdge(int u, int v, int w) {
    Node *p = (Node*)malloc(sizeof(Node));
    p->v = v;
    p->w = w;
    p->next = adj[u];
    adj[u] = p;
}

int main() {
    int N, M, C, K;

    while (1) {
        scanf("%d %d %d %d", &N, &M, &C, &K);
        if (N == 0 && M == 0 && C == 0 && K == 0) break;

        // limpa listas
        for (int i = 0; i < N; i++) {
            adj[i] = NULL;
        }

        for (int i = 0; i < M; i++) {
            int u, v, p;
            scanf("%d %d %d", &u, &v, &p);

            if (u < C && v < C) {
                // ambas na rota
                if (v == u + 1) addEdge(u, v, p);
                if (u == v + 1) addEdge(v, u, p);
            }
            else if (u < C && v >= C) {
                // entrando na rota => só pode ir da grande para a rota
                addEdge(v, u, p);
            }
            else if (u >= C && v < C) {
                // idem ao caso simétrico
                addEdge(u, v, p);
            }
            else {
                // ambas >= C: trânsito livre
                addEdge(u, v, p);
                addEdge(v, u, p);
            }
        }

        // Dijkstra
        for (int i = 0; i < N; i++) {
            dist[i] = INF;
            used[i] = 0;
        }

        dist[K] = 0;

        for (int i = 0; i < N; i++) {
            int u = -1;
            int best = INF;

            for (int j = 0; j < N; j++) {
                if (!used[j] && dist[j] < best) {
                    best = dist[j];
                    u = j;
                }
            }

            if (u == -1) break;
            used[u] = 1;

            // relaxação
            for (Node *p = adj[u]; p != NULL; p = p->next) {
                int v = p->v;
                int w = p->w;

                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                }
            }
        }

        printf("%d\n", dist[C-1]);
    }

    return 0;
}
