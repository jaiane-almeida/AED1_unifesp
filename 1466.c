#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int valor;
    struct No *esq, *dir;
} No;

// ----------------- Cria nodo ------------------
No* novoNo(int v) {
    No *n = (No*) malloc(sizeof(No));
    n->valor = v;
    n->esq = NULL;
    n->dir = NULL;
    return n;
}

// ----------------- Insere na BST ------------------
No* inserir(No *raiz, int v) {
    if (raiz == NULL)
        return novoNo(v);

    if (v < raiz->valor)
        raiz->esq = inserir(raiz->esq, v);
    else
        raiz->dir = inserir(raiz->dir, v);

    return raiz;
}

// ----------------- FILA para BFS ------------------
No* fila[1000];
int inicio, fim;

void enfileira(No *n) {
    fila[fim++] = n;
}

No* desenfileira() {
    return fila[inicio++];
}

int filaVazia() {
    return inicio == fim;
}

// ----------------- BFS (Percurso por nível) ------------------
void bfs(No *raiz) {
    inicio = 0;
    fim = 0;

    enfileira(raiz);

    int primeiro = 1;

    while (!filaVazia()) {
        No *atual = desenfileira();

        if (!primeiro)
            printf(" ");
        printf("%d", atual->valor);
        primeiro = 0;

        if (atual->esq != NULL)
            enfileira(atual->esq);

        if (atual->dir != NULL)
            enfileira(atual->dir);
    }
}

// ----------------- MAIN ------------------
int main() {

    int C;
    scanf("%d", &C);

    for (int caso = 1; caso <= C; caso++) {

        int N;
        scanf("%d", &N);

        No *raiz = NULL;

        for (int i = 0; i < N; i++) {
            int x;
            scanf("%d", &x);
            raiz = inserir(raiz, x);
        }

        printf("Case %d:\n", caso);
        bfs(raiz);
        printf("\n\n");  // linha em branco após cada caso
    }

    return 0;
}
