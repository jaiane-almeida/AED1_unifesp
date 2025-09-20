#include <stdio.h>

int main() {
    int k, i, j, m;
    int matriz[9][9];

    scanf("%d", &k);

    int errosLinha[k], errosColuna[k], errosBloco[k];

    for (m = 0; m < k; m++) {
        int erroLinha = 0, erroColuna = 0, erroBloco = 0;

        for (i = 0; i < 9; i++) {
            for (j = 0; j < 9; j++) {
                scanf("%d", &matriz[i][j]);
            }
        }

        for (i = 0; i < 9 && !erroLinha; i++) {
            int numeros[10] = {0};
            for (j = 0; j < 9; j++) {
                int valor = matriz[i][j];
                if (valor < 1 || valor > 9 || numeros[valor]) {
                    erroLinha = 1;
                    break;
                }
                numeros[valor] = 1;
            }
        }

        for (j = 0; j < 9 && !erroColuna; j++) {
            int numeros[10] = {0};
            for (i = 0; i < 9; i++) {
                int valor = matriz[i][j];
                if (valor < 1 || valor > 9 || numeros[valor]) {
                    erroColuna = 1;
                    break;
                }
                numeros[valor] = 1;
            }
        }

        for (int linhaBloco = 0; linhaBloco < 9 && !erroBloco; linhaBloco += 3) {
            for (int colunaBloco = 0; colunaBloco < 9 && !erroBloco; colunaBloco += 3) {
                int numeros[10] = {0};
                for (i = linhaBloco; i < linhaBloco + 3; i++) {
                    for (j = colunaBloco; j < colunaBloco + 3; j++) {
                        int valor = matriz[i][j];
                        if (valor < 1 || valor > 9 || numeros[valor]) {
                            erroBloco = 1;
                            break;
                        }
                        numeros[valor] = 1;
                    }
                    if (erroBloco) break;
                }
            }
        }

        errosLinha[m] = erroLinha;
        errosColuna[m] = erroColuna;
        errosBloco[m] = erroBloco;
    }

    for (m = 0; m < k; m++) {
        printf("Instancia %d\n", m + 1);
        if (!errosLinha[m] && !errosColuna[m] && !errosBloco[m]) {
            printf("SIM\n");
        } else {
            printf("NAO\n");
        }
        printf("\n"); // quebra de linha após TODAS as instâncias, inclusive a última
    }

    return 0;
}
