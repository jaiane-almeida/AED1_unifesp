#include <stdio.h> //filas com referencias de local 

#define MAX_ID 100000  // limite máximo de identificadores

int main() {
    int N, M;
    int fila[50000];
    int saiu[MAX_ID + 1] = {0}; // vetor de marcação (hash simples)

    // lê o número de pessoas na fila
    scanf("%d", &N);

    // lê os identificadores da fila inicial
    for (int i = 0; i < N; i++) {
        scanf("%d", &fila[i]);
    }

    // lê a quantidade de pessoas que saíram
    scanf("%d", &M);

    // marca as pessoas que saíram
    for (int i = 0; i < M; i++) {
        int id;
        scanf("%d", &id);
        saiu[id] = 1;
    }

    // imprime quem ficou na fila
    int primeiro = 1;
    for (int i = 0; i < N; i++) {
        if (!saiu[fila[i]]) {
            if (!primeiro) printf(" ");
            printf("%d", fila[i]);
            primeiro = 0;
        }
    }
    printf("\n");

    return 0;
}
