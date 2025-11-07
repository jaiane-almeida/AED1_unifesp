//bolsa altura

#include <stdio.h>
#include <stdlib.h>

// Função de comparação para qsort
int compara(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int NC;
    scanf("%d", &NC); // Número de cidades

    while (NC--) {
        int N;
        scanf("%d", &N); // Número de pessoas na cidade

        int *alturas = (int *)malloc(N * sizeof(int));
        if (!alturas) {
            fprintf(stderr, "Erro de alocação de memória\n");
            return 1;
        }

        for (int i = 0; i < N; i++) {
            scanf("%d", &alturas[i]);
        }

        qsort(alturas, N, sizeof(int), compara); // Ordena as alturas

        for (int i = 0; i < N; i++) {
            printf("%d", alturas[i]);
            if (i < N - 1) printf(" ");
        }
        printf("\n");

        free(alturas); // Libera memória
    }

    return 0;
}
