//calculando o numero de nós de uma arvore binária 

#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura do nó
typedef struct No {
    int valor;
    struct No* esq;
    struct No* dir;
} No;

// Função para criar um novo nó
No* criarNo(int valor) {
    No* novo = (No*) malloc(sizeof(No));
    novo->valor = valor;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

// Função recursiva para contar o número de nós
int qtd(No* conteudo) {
    if (conteudo == NULL) {
        return 0;
    }
    return 1 + qtd(conteudo->esq) + qtd(conteudo->dir);
}

int main() {
    // Criando manualmente uma árvore de exemplo:
    //        10
    //       /  \
    //      5    20
    //     / \     \
    //    3   7     30

    No* raiz = criarNo(10);
    raiz->esq = criarNo(5);
    raiz->dir = criarNo(20);
    raiz->esq->esq = criarNo(3);
    raiz->esq->dir = criarNo(7);
    raiz->dir->dir = criarNo(30);

    // Chamando a função para contar os nós
    int total = qtd(raiz);

    printf("A árvore possui %d nós.\n", total);

    return 0;
}
