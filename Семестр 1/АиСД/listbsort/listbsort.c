#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Elem { struct Elem *next; char *word; } Elem;

char* w[2000];

#define swap(a, b)                                                         \
  {                                                                        \
    char* t = a->word;                                                     \
    a->word = b->word;                                                     \
    b->word = t;                                                           \
  }

struct Elem *bsort(struct Elem *list) {
    Elem* i;
    for (Elem* now = NULL; now != list; now = i) {
        i = list;
        for (; i->next != now; i = i->next) {
            if (strlen(i->next->word) < strlen(i->word)) {
                swap(i->next, i);
            }
        }
    }
    return list;
}

signed main() {
    Elem* list = NULL;

    int cnt = 0;
    for (; scanf("%ms", &w[cnt]) != EOF; ) {
        ++cnt;
    }

    for (; cnt > 0; ) {
        --cnt;
        Elem* new = malloc(sizeof(Elem));
        new->word = w[cnt];
        new->next = list;
        list = new;
    }

    list = bsort(list);

    for (; list; ) {
        Elem* next = list->next;
        printf("%s ", list->word);
        free(list->word);
        free(list);
        list = next;
    }

    return 0;
}
