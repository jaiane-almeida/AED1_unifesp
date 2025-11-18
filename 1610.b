#include <stdio.h>        // Biblioteca padrão para entrada e saída
#include <string.h>       // Usada para funções como memset (se precisar)

#define MAX 10005         // Máximo de documentos (N)
#define MAXM 30005        // Máximo de dependências (M)


// DECLARAÇÃO DAS ESTRUTURAS DA LISTA DE ADJ.


int head[MAX];            // head[u] guarda o índice da 1ª aresta que sai de u
int to[MAXM];             // to[i] = vértice onde a i-ésima aresta chega
int next[MAXM];           // next[i] = próxima aresta que sai do mesmo vértice
                          // (uso de lista encadeada compacta)

int estado[MAX];          // 0 = não visitado, 1 = visitando, 2 = terminado
int N, M;                 // N = documentos, M = dependências
int pos;                  // posição atual de inserção no vetor de arestas
int achou_ciclo;          // flag para indicar se um ciclo foi encontrado


// FUNÇÃO PARA ADICIONAR UMA ARESTA U → V NO GRAFO

void add(int u, int v) {
    to[pos] = v;          // registra que a aresta pos vai para o vértice v
    next[pos] = head[u];  // ela aponta para a antiga primeira aresta de u
    head[u] = pos;        // agora "pos" é a nova primeira aresta de u
    pos++;                // avança posição para próxima inserção
}


// DFS PARA DETECTAR CICLO NO GRAFO DIRIGIDO
//psq mais sobre
void dfs(int u) {
    estado[u] = 1;        // marca u como “visitando”

    // percorre todas as arestas que saem de u
    for (int e = head[u]; e != -1; e = next[e]) {
        int v = to[e];    // v é o vértice atingido pela aresta u → v

        if (estado[v] == 1) { // se v está sendo visitado agora mesmo...
            achou_ciclo = 1;  // então encontramos um ciclo
            return;           // encerra DFS imediatamente
        }

        if (estado[v] == 0) { // se ainda não visitamos v...
            dfs(v);           // visita v
            if (achou_ciclo)  // se o DFS achar ciclo em qualquer ponto...
                return;       // interrompe propagando a informação
        }
    }

    estado[u] = 2;        // marca u como totalmente visitado
}


int main() {
    int T;                // número de casos de teste
    scanf("%d", &T);      // lê T

    // LOOP PRINCIPAL: processa cada caso
    while (T--) {

        scanf("%d %d", &N, &M);  
        // Lê N (documentos) e M (dependências)

        // Inicializa listas e estados
        for (int i = 1; i <= N; i++) {
            head[i] = -1;  // indica que o vértice i ainda não tem arestas
            estado[i] = 0; // marca todos os vértices como não visitados
        }

        pos = 0;          // reseta a posição do vetor de arestas

        // Lê cada dependência
        for (int i = 0; i < M; i++) {
            int A, B;
            scanf("%d %d", &A, &B);  
            add(A, B);     //

