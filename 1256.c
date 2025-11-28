#include <stdio.h>
#include <string.h>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int M, C;
        scanf("%d %d", &M, &C);

        int hash[101][200];  // M <= 100, cada lista até 200 chaves
        int size[101];

        memset(size, 0, sizeof(size));

        for (int i = 0; i < C; i++) {
            int x;
            scanf("%d", &x);
            int idx = x % M;
            hash[idx][ size[idx]++ ] = x;
        }

        for (int i = 0; i < M; i++) {
            printf("%d ->", i);
            for (int j = 0; j < size[i]; j++) {
                printf(" %d ->", hash[i][j]);
            }
            printf(" \\\n");  // apenas uma barra invertida
        }

        if (T) printf("\n");  // separa os casos com linha em branco
    }

    return 0;
}
