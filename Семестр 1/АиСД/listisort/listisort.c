#include <stdio.h>
#include <stdlib.h>

#define INF 2147483647

typedef struct Elem {
    struct Elem *prev, *next;
    int v;
} List;

List* list;

void push(int x) {
    List* ins = malloc(sizeof(List));
    ins->prev = list;
    ins->next = list->next;
    ins->v = x;
    list->next->prev = ins;
    list->next = ins;
}

void Sorting() {
    List *t, *swap, *iterator = list->next->next;
    for (; iterator != list; ) {
        t = iterator->next, swap = iterator->prev;
        for (; (swap->v > iterator->v) && (swap != list); swap = swap->prev) {}
        iterator->prev->next = iterator->next;
        iterator->next->prev = iterator->prev;
        iterator->prev = swap;
        iterator->next = swap->next;
        swap->next->prev = iterator;
        swap->next = iterator;
        iterator = t;
    }
}

int main() {
    list = malloc(sizeof(List));
    list->prev = list;
    list->next = list;
    list->v = INF;

    int n, x;
    scanf("%d", &n);
    for (; n--;) {
        scanf("%d", &x);
        push(x);
    }

    List* end = list;
    for (list = list->next; list != end; list = list->next) {
        printf("%d ", list->v);
    }

    end = list;
    for (list = list->next; list != end; ) {
        list = list->next;
        free(list->prev);
    }

    //free(end);

    return 0;
}
