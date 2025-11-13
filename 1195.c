//exericios de Árvore Binária de Busca

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int v;
    struct node *l, *r;
} Node;

Node* insert(Node* root, int val) {
    if (root == NULL) {
        root = (Node*) malloc(sizeof(Node));
        root->v = val;
        root->l = root->r = NULL;
        return root;
    }
    if (val < root->v) root->l = insert(root->l, val);
    else root->r = insert(root->r, val);
    return root;
}

void prefix(Node* root, int *first) {
    if (root == NULL) return;
    if (*first) { printf("%d", root->v); *first = 0; }
    else printf(" %d", root->v);
    prefix(root->l, first);
    prefix(root->r, first);
}

void infix(Node* root, int *first) {
    if (root == NULL) return;
    infix(root->l, first);
    if (*first) { printf("%d", root->v); *first = 0; }
    else printf(" %d", root->v);
    infix(root->r, first);
}

void postfix(Node* root, int *first) {
    if (root == NULL) return;
    postfix(root->l, first);
    postfix(root->r, first);
    if (*first) { printf("%d", root->v); *first = 0; }
    else printf(" %d", root->v);
}

void freeTree(Node* root) {
    if (root == NULL) return;
    freeTree(root->l);
    freeTree(root->r);
    free(root);
}

int main() {
    int C;
    scanf("%d", &C);

    for (int c = 1; c <= C; c++) {
        int N, x;
        scanf("%d", &N);

        Node* root = NULL;

        for (int i = 0; i < N; i++) {
            scanf("%d", &x);
            root = insert(root, x);
        }

        printf("Case %d:\n", c);

        int first = 1;
        printf("Pre.: ");
        prefix(root, &first);
        printf("\n");

        first = 1;
        printf("In..: ");
        infix(root, &first);
        printf("\n");

        first = 1;
        printf("Post: ");
        postfix(root, &first);
        printf("\n\n");

        freeTree(root);
    }

    return 0;
}
