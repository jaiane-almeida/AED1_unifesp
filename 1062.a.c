#include <stdio.h>
//exercicios de trilhos ordenações de vagões feito por pilha 
int main() {
    int n;
    while (scanf("%d", &n) && n) {
        while (1) {
            int seq[1000];
            scanf("%d", &seq[0]);
            if (seq[0] == 0) break;

            for (int i = 1; i < n; i++)
                scanf("%d", &seq[i]);

            int stack[1000];
            int top = -1;
            int next = 1;  // próximo vagão a entrar
            int i = 0;     // posição na sequência desejada

            while (next <= n) {
                stack[++top] = next++;  // entra na pilha

                // enquanto o topo for o vagão que precisamos, tiramos da pilha
                while (top >= 0 && stack[top] == seq[i]) {
                    top--;
                    i++;
                }
            }

            if (top == -1)
                printf("Yes\n");
            else
                printf("No\n");
        }
        printf("\n"); // linha em branco após o bloco
    }
    return 0;
}
