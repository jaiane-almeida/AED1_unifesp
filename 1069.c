#include <stdio.h>
#include <string.h>

int main() {
    int N;
    scanf("%d", &N);

    while (N--) {
        char s[1100];
        scanf("%s", s);

        int aberturas = 0, diamantes = 0;

        for (int i = 0; s[i] != '\0'; i++) {
            if (s[i] == '<') {
                aberturas++;
            }
            else if (s[i] == '>' && aberturas > 0) {
                diamantes++;
                aberturas--;
            }
        }

        printf("%d\n", diamantes);
    }
    return 0;
}
