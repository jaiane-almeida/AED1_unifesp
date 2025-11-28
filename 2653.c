#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRINGS 1000000  // limite total de caracteres
#define MAX_LEN     1000000  // limite total de caracteres somados

// Função de comparação para qsort
int cmp(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

int main() {
    char *joias[1000000];  // ponteiros para strings
    int n = 0;
    char buffer[1000005];

    // leitura até EOF
    while (scanf("%s", buffer) == 1) {
        joias[n] = strdup(buffer); // duplica a string lida
        n++;
    }

    // ordena todas as strings
    qsort(joias, n, sizeof(char *), cmp);

    // conta distintas
    int distintos = 0;
    for (int i = 0; i < n; i++) {
        if (i == 0 || strcmp(joias[i], joias[i-1]) != 0) {
            distintos++;
        }
    }

    printf("%d\n", distintos);

    // libera memória
    for (int i = 0; i < n; i++) {
        free(joias[i]);
    }

    return 0;
}
