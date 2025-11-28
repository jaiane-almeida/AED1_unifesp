#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "uthash.h"

typedef struct {
    char *str;
    UT_hash_handle hh;
} Item;

int main() {
    char buffer[1000005];
    Item *set = NULL;

    while (scanf("%s", buffer) != EOF) {
        Item *s;

        HASH_FIND_STR(set, buffer, s);
        if (!s) {
            s = malloc(sizeof(Item));
            s->str = strdup(buffer);
            HASH_ADD_KEYPTR(hh, set, s->str, strlen(s->str), s);
        }
    }

    printf("%u\n", HASH_COUNT(set));

    return 0;
}
