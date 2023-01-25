//Засчитываю. Вот эти операции «++q->tail; if (q->tail == q->cap) { q->tail = 0; }» нужно выполнять независимо от значения q->size.

#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    typedef struct {
        int* data;
        long long cap, size, head, tail;
    } TypeQueue;

    TypeQueue* make_queue() {
        TypeQueue* q;

        q = malloc(sizeof(TypeQueue));
        q->cap = 3;
        q->data = malloc(q->cap * sizeof(int));
        q->size = 0;
        q->head = 0;
        q->tail = 0;
        return q;
    }

    void push(TypeQueue* q, int v) {
        if (q->size == q->cap) {
            int* new = malloc((q->cap * 3) * sizeof(int));
            size_t i = q->head;
            size_t new_i = 0;
            for (; i != q->tail; ) {
                new[new_i] = q->data[i];
                ++new_i;
                ++i;
                if (i == q->cap) {
                    i = 0;
                }
            }
            new[new_i] = q->data[i];
            free(q->data);
            q->data = new;
            q->cap *= 3;
            q->head = 0;
            q->tail = new_i;
        }
        if (q->size) {
            ++q->tail;
            if (q->tail == q->cap) {
                q->tail = 0;
            }
        }
        q->data[q->tail] = v;
        ++q->size;
    }

    int front(TypeQueue* q) {
        return q->data[q->head];
    }

    int empty(TypeQueue* q) {
        return (q->size ? 0 : 1);
    }

    void clean(TypeQueue* q) {
        free(q->data);
        free(q);
    }

    int pop(TypeQueue* q) {
        int v = front(q);

        --q->size;
        if (q->size) {
            ++q->head;
        }

        if (q->head == q->cap) {
            q->head = 0;
        }

        return v;
    }

    signed main() {
        TypeQueue* q = make_queue();

        char* cmd;
        int x;
        for ( ; 0 == 0; ) {
            scanf("%ms", &cmd);

            if (strcmp(cmd, "ENQ") == 0) {
                scanf("%d", &x);
                push(q, x);
            }

            if (strcmp(cmd, "DEQ") == 0) {
                printf("%d\n", pop(q));
            }

            if (strcmp(cmd, "EMPTY") == 0) {
                (empty(q) ? printf("true\n") : printf("false\n"));
            }

            if (strcmp(cmd, "END") == 0) {
                free(cmd);
                break;
            }

            free(cmd);
        }

        clean(q);

        return 0;
    }
