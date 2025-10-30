//exericicio feofiloff de buscar e remover item 

#include <stdio.h>
#include <stdlib.h>

typedef struct celula {
    int conteudo;
    struct celula *seg;
} celula;

void BuscaERemove(celula **head, int key) {
    celula *p = *head;     // ponteiro atual
    celula *ant = NULL;    // ponteiro para o anterior

    // percorre até achar o elemento ou o fim
    while (p != NULL && p->conteudo != key) {
        ant = p;
        p = p->seg;
    }

    // se não encontrou, sai da função
    if (p == NULL) {
        printf("Elemento %d não encontrado.\n", key);
        return;
    }

    // caso 1: o nó a remover é o primeiro
    if (ant == NULL) {
        *head = p->seg;  // atualiza a cabeça
    } else {
        // caso 2: nó está no meio ou fim
        ant->seg = p->seg;
    }

    free(p); // libera memória
}

  
