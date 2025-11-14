/*Dado o endereço x de um nó em uma árvore binária, considere a sequência de
endereços que se obtém pela iteração das atribuições x = x->esq e x = x->dir em
qualquer ordem. Mostre que esta sequência descreve um caminho*/


#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int valor;
    struct no *esq, *dir;
} No; // criando a estrutura de um nó generico, deixando claro quais dados inciais que sempre vamos precisar, no caso, valor do pai e seus filhos direito e esquerdo 

// cria novo nó, o que iremos fazer com a estrutura dos dados que pegamos? 
No* novoNo(int v) { //esse int v é um parametro que iremos acessar pela int main 
    No* n = (No*) malloc(sizeof(No)); //criando um ponteiro que aponta para a estrutura do nó que estamos criando, essa  estrutura cresce dinamicamente a medida que valor, esq e dir vão crescendo 
    n->valor = v;
    n->esq = n->dir = NULL; //aqui estamos dizendo que ele começa com valores vazios 
    return n; // e retorna o que criamos 
}

//AQUI TEMOS O MOLHO MAIS IMPORTANTE QUE FAZ O QUE PRECISAMOS, VARRER A ARVORE
// percorre aplicando comandos: 'E' = esquerda, 'D' = direita

void percorre(No *x, char *comandos) { //*x é um ponteiro que só recebe valores NULL, esq e dir e *comandos, é valor que será pego da int main
    printf("Início no nó: %d\n", x->valor);

    for (int i = 0; comandos[i] != '\0'; i++) { //percorre um laçoaté encontrar o fim 
        if (comandos[i] == 'E') { //se ele encontrar o atributo E que vem de comandos (como ele liga i em comandos? comandos[i] )
            if (x->esq == NULL) break; //se o espaço de esq estiver vaazio ele quebra para não acessar memoria vazia 
            x = x->esq;
        } else if (comandos[i] == 'D') {
            if (x->dir == NULL) break;
            x = x->dir;
        }
        printf("Visitando nó: %d\n", x->valor);
    }
}

int main() {
    /*
           1
          / \
         2   3
        / \
       4   5
    */

    No *raiz = novoNo(1);
    raiz->esq = novoNo(2);
    raiz->dir = novoNo(3);
    raiz->esq->esq = novoNo(4);
    raiz->esq->dir = novoNo(5);

    // sequência arbitrária de esquerda e direita
    char comandos[] = "EED";  // vai para 2, depois 4, depois para direita (para em NULL)

    percorre(raiz, comandos); //raiz é atribuida ao int v 

    return 0;
}
