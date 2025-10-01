
//**************EXERCICIO DO BEECROWD ****************

#include <stdio.h>

#define limite 1000//definindo quando vale uma variavel 

int main() {
int qtd[limite]; // coloco a variavel dentro do vetor 
int n, menor, posicao, i;

  scanf("%d", &n);

  if(n>limite){
      printf("Esse numero não é valido");
      return 1;
  }
  
  for(i =0; i<n; i++){
    scanf("%d", &qtd[i]);
}

  menor = qtd[0];
  posicao = 0;
  
  for (i = 1; i < n; i++) {
      if (qtd[i] < menor) {
          menor = qtd[i];
          posicao = i; 
      }
  }

  printf("Menor valor: %d", menor);
  printf("\nPosicao: %d\n", posicao);//pq a posição começa no zero

return 0;

}
