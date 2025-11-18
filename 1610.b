#include <stdio.h>
#include <string.h>

#define MAX 10005
#define MAXM 30005   // número máximo de dependências

// Lista de adjacência:
int head[MAX], to[MAXM], next[MAXM];
int estado[MAX];  // 0 = não visitado, 1 = visitando, 2 = terminado
int N, M;
int pos;          // posição atual para inserir arestas
int achou_ciclo;


void add(int u, int v) { // add aresta
    to[pos] = v;
    next[pos] = head[u];
    head[u] = pos;
    pos++;
}

//detecta ciclo
void dfs(int u) { 
    estado[u] = 1; // visitando

    for (int e = head[u]; e != -1; e = next[e]) {
        int v = to[e];

        if (estado[v] == 1) {
            achou_ciclo = 1;
            return;
        }
        if (estado[v] == 0) {
            dfs(v);
            if (achou_ciclo) return;
        }
    }

    estado[u] = 2; // terminou completamente
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {

        scanf("%d %d", &N, &M);

        // inicializar listas
        for (int i = 1; i <= N; i++) {
            head[i] = -1;
            estado[i] = 0;
        }

        pos = 0;

        // ler as dependências
        for (int i = 0; i < M; i++) {
            int A, B;
            scanf("%d %d", &A, &B);
            add(A, B); // A depende de B
        }

        achou_ciclo = 0;

        // rodar DFS em todos os nós ainda não visitados
        for (int i = 1; i <= N; i++) {
            if (estado[i] == 0) {
                dfs(i);
                if (achou_ciclo) break;
            }
        }

        if (achou_ciclo)
            printf("SIM\n");
        else
            printf("NAO\n");
    }

    return 0;
}
