#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No {
    char valor;
    struct No *esq;
    struct No *dir;
} No;

No *novoNo(char v) {
    No *n = (No*) malloc(sizeof(No));
    n->valor = v;
    n->esq = n->dir = NULL;
    return n;
}

No *insere(No *raiz, char novo) {
    if (raiz == NULL)
        return novoNo(novo);

    if (novo < raiz->valor)
        raiz->esq = insere(raiz->esq, novo);
    else if (novo > raiz->valor)
        raiz->dir = insere(raiz->dir, novo);

    return raiz;
}

/* ----- VARIÁVEL GLOBAL PARA FORMATAR SAÍDA ----- */
int primeiro;

/* ----- PERCURSOS SEM ESPAÇO NO FINAL ----- */
void infixa(No *raiz) {
    if (raiz == NULL) return;

    infixa(raiz->esq);

    if (!primeiro) printf(" ");
    printf("%c", raiz->valor);
    primeiro = 0;

    infixa(raiz->dir);
}

void prefixa(No *raiz) {
    if (raiz == NULL) return;

    if (!primeiro) printf(" ");
    printf("%c", raiz->valor);
    primeiro = 0;

    prefixa(raiz->esq);
    prefixa(raiz->dir);
}

void posfixa(No *raiz) {
    if (raiz == NULL) return;

    posfixa(raiz->esq);
    posfixa(raiz->dir);

    if (!primeiro) printf(" ");
    printf("%c", raiz->valor);
    primeiro = 0;
}

/* ----- BUSCA ----- */
int sera(No *raiz, char n) {
    if (raiz == NULL)
        return 0;

    if (n == raiz->valor)
        return 1;

    if (n < raiz->valor)
        return sera(raiz->esq, n);

    return sera(raiz->dir, n);
}

int main() {
    No *raiz = NULL;
    char comando[20];
    char c;

    while (scanf("%s", comando) != EOF) {

        if (strcmp(comando, "I") == 0) {
            scanf(" %c", &c);
            raiz = insere(raiz, c);
        }
        else if (strcmp(comando, "INFIXA") == 0) {
            primeiro = 1;
            infixa(raiz);
            printf("\n");
        }
        else if (strcmp(comando, "PREFIXA") == 0) {
            primeiro = 1;
            prefixa(raiz);
            printf("\n");
        }
        else if (strcmp(comando, "POSFIXA") == 0) {
            primeiro = 1;
            posfixa(raiz);
            printf("\n");
        }
        else if (strcmp(comando, "P") == 0) {
            scanf(" %c", &c);
            if (sera(raiz, c))
                printf("%c existe\n", c);
            else
                printf("%c nao existe\n", c);
        }
    }

    return 0;
}
