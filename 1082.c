#include <stdio.h>
#include <string.h>

#define MAX 26

int visited[MAX];
int adj[MAX][MAX];
int V, E;

int comp[MAX];  // armazena os vértices do componente
int comp_size;

void dfs(int v) {
    visited[v] = 1;
    comp[comp_size++] = v;  // adiciona no componente

    for (int i = 0; i < V; i++) {
        if (adj[v][i] && !visited[i]) {
            dfs(i);
        }
    }
}

void sort_component() {
    for (int i = 0; i < comp_size; i++) {
        for (int j = i + 1; j < comp_size; j++) {
            if (comp[j] < comp[i]) {
                int tmp = comp[i];
                comp[i] = comp[j];
                comp[j] = tmp;
            }
        }
    }
}

int main() {
    int N;
    scanf("%d", &N);

    for (int caso = 1; caso <= N; caso++) {

        scanf("%d %d", &V, &E);

        memset(adj, 0, sizeof(adj));
        memset(visited, 0, sizeof(visited));

        for (int i = 0; i < E; i++) {
            char a, b;
            scanf(" %c %c", &a, &b);
            int u = a - 'a';
            int v = b - 'a';
            adj[u][v] = adj[v][u] = 1;
        }

        printf("Case #%d:\n", caso);

        int componentes = 0;

        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                comp_size = 0;

                dfs(i);           // coleta os vértices do componente
                sort_component(); // ordena alfabeticamente

                componentes++;

                // imprime o componente em ordem
                for (int k = 0; k < comp_size; k++) {
                    printf("%c,", comp[k] + 'a');
                }
                printf("\n");
            }
        }

        printf("%d connected components\n\n", componentes);
    }

    return 0;
}
