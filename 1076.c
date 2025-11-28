#include <stdio.h>
#include <stdlib.h>

#define MAXV 60  // V <= 49 (7x7), usar folga

int V;                  // número de vértices
int adjMat[MAXV][MAXV]; // 0/1 para aresta única entre i e j
int degv[MAXV];
int visited[MAXV];
int p_odd[MAXV];        // 1 se grau ímpar
int added;              // contagem de arestas a duplicar (custo extra)

// DFS retorna número de vértices ímpares na subárvore do `u` (contando u),
// percorrendo sem retornar ao pai.
int dfs_count_odd(int u, int parent) {
    visited[u] = 1;
    int count = p_odd[u];
    for (int v = 0; v < V; v++) {
        if (adjMat[u][v] && v != parent) {
            if (!visited[v]) {
                int sub = dfs_count_odd(v, u);
                if (sub % 2 == 1) {
                    // esta aresta (u-v) precisa ser duplicada uma vez
                    added++;
                }
                count += sub;
            }
        }
    }
    return count;
}

int main() {
    int T;
    if (scanf("%d", &T) != 1) return 0;

    while (T--) {
        int start;
        if (scanf("%d", &start) != 1) return 0;

        int A;
        if (scanf("%d %d", &V, &A) != 2) return 0;

        // inicializa
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) adjMat[i][j] = 0;
            degv[i] = 0;
            visited[i] = 0;
            p_odd[i] = 0;
        }

        // lê arestas e deduplica (considera grafo não dirigido simples)
        for (int i = 0; i < A; i++) {
            int u, v;
            scanf("%d %d", &u, &v);
            // caso o input possa ter índices fora de 0..V-1, assume-se que os inputs estão corretos (ex.: 0..V-1)
            if (u < 0 || v < 0 || u >= V || v >= V) continue;
            if (!adjMat[u][v]) { // se ainda não existe, adiciona
                adjMat[u][v] = adjMat[v][u] = 1;
                degv[u]++; degv[v]++;
            }
            // caso já exista (aresta paralela), ignoramos (opcional)
        }

        // conta arestas únicas W
        int W = 0;
        for (int i = 0; i < V; i++)
            for (int j = i+1; j < V; j++)
                if (adjMat[i][j]) W++;

        // marca pares ímpares
        for (int i = 0; i < V; i++) p_odd[i] = (degv[i] % 2 != 0) ? 1 : 0;

        // se não há arestas, movimentos = 0
        if (W == 0) {
            printf("0\n");
            continue;
        }

        // zerar visited e added
        for (int i = 0; i < V; i++) visited[i] = 0;
        added = 0;

        // executar DFS a partir do nó start
        // Nota: enunciado presume que o desenho é possível sem levantar caneta (grafo conexo em termos de arestas),
        // mas se start estiver em componente sem arestas, o DFS cobrirá apenas essa componente.
        // Ainda assim, usamos a mesma estratégia pois casos inválidos não aparecem no juízo do problema.
        dfs_count_odd(start, -1);

        // Se o grafo tiver componentes não alcançáveis a partir de start mas com arestas,
        // teoricamente seria impossível desenhar tudo sem levantar caneta. O enunciado não trata esse caso,
        // portanto assumimos que não ocorrerá (entrada válida).
        // (Se quiser checar: somar W_reach e comparar com W).

        int result = W + added;
        printf("%d\n", result);
    }

    return 0;
}
