
//esse exercicio é para mostrar o numero menor e em qual posição ele está 

#include <stdio.h>
#include <stdlib.h> // necessário para malloc e free


int main() {
    int n, menor, posicao; 
    printf("Digite os numeros que voce quer: ");
    scanf("%d", &n);

    // aloca dinamicamente memória para 'n' inteiros
    int *vetor = (int *) malloc(n * sizeof(int));

  // preenchendo o vetor
    for (int i = 0; i < n; i++) {
      scanf("%d", &vetor[i]);
    }

    if (vetor == NULL) { //Você precisa verifica r antes para evitar acessar memória inválida.
        printf("Erro: memória não alocada!\n");
        return 1; // encerra o programa
    }

    // mostrando o vetor só pra testar
    for (int i = 0; i < n; i++) {
        printf("%d ", vetor[i]);
    }

    menor = vetor[0];
    posicao = 0;

    for (int i = 1; i < n; i++) {
        if (vetor[i] < menor) {
            menor = vetor[i];
            posicao = i; 
        }
    }

    printf("Menor valor: %d", menor);
    printf("\nPosicao: %d\n", posicao +1);

    // libera a memória alocada
    free(vetor);

    return 0;
}

