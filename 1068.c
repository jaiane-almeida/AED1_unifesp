#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char c;
    struct Node *next;
} Node;

Node* push(Node *top, char c) {
    Node *newNode = (Node*) malloc(sizeof(Node));
    newNode->c = c;
    newNode->next = top;
    return newNode;
}

Node* pop(Node *top) {
    Node *temp = top;
    top = top->next;
    free(temp);
    return top;
}

int main() {
    char expr[1100];

    while (scanf("%s", expr) != EOF) {

        Node *stack = NULL;
        int correct = 1;

        for (int i = 0; expr[i] != '\0'; i++) {

            if (expr[i] == '(') {
                stack = push(stack, '(');
            }

            else if (expr[i] == ')') {
                if (stack == NULL) {  
                    correct = 0;      // fecha sem abrir
                    break;
                }
                stack = pop(stack);
            }
        }

        // Se ainda houver coisa na pilha → parênteses não fechados
        if (stack != NULL)
            correct = 0;

        // libera qualquer lixo restante
        while (stack != NULL)
            stack = pop(stack);

        if (correct)
            printf("correct\n");
        else
            printf("incorrect\n");
    }

    return 0;
}
