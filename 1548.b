#include <stdio.h>
#include <stdlib.h> // fila do recreio 

// Função de comparação para qsort (ordem decrescente)
int cmp(const void *a, const void *b) {
    return (*(int*)b - *(int*)a);
}

int main() {
    int n; // número de casos de teste
    scanf("%d", &n);

    while (n--) {
        int m;
        scanf("%d", &m);

        int original[1000];
        int ordenado[1000];

        // Lê as notas
        for (int i = 0; i < m; i++) {
            scanf("%d", &original[i]);
            ordenado[i] = original[i]; // copia para o vetor que será ordenado
        }

        // Ordena em ordem decrescente
        qsort(ordenado, m, sizeof(int), cmp);

        // Conta quantos não mudaram de posição
        int cont = 0;
        for (int i = 0; i < m; i++) {
            if (original[i] == ordenado[i])
                cont++;
        }

        printf("%d\n", cont);
    }

    return 0;
}
