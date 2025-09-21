include <stdio.h>

#define limite 1000

int main() {
    int qtd[limite]; 
    int n, i, posicao;
    int menor;
    int *m; 

    printf("Escreva um valor para o tamanho do seu vetor: ");
    scanf("%d", &n);

    if(n > limite || n <= 0) {
        printf("Esse numero não é valido, insira um numero até 1000 e que seja maior que 0");
        return 1;
    }

    printf("Digite os numeros que voce gostaria de colocar no vetor separados por espaço: ");
    for(i = 0; i < n; i++) {
        scanf("%d", &qtd[i]);
    }

    // Inicializa
    menor = qtd[0];
    posicao = 0;
    m = &menor; 

    // Percorrendo o vetor usando ponteiro
    for (i = 1; i < n; i++) {
        if (*(qtd + i) < *m) {
            menor = *(qtd + i);
            posicao = i;
        }
    }

    printf("Menor valor: %d\n", *m);
    printf("Posição: %d\n", posicao +1);

    return 0;
