#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int* data;
    unsigned int cap;
    unsigned int size;
} Typestack;

Typestack* stack_init() {
    Typestack* stack = (Typestack*)malloc(sizeof(Typestack));
    stack->cap = 10;
    stack->size = 0;
    stack->data = malloc(10 * sizeof(int));
    return stack;
}

void clean(Typestack* stack) {
    free(stack->data);
    free(stack);
}

void push(Typestack* stack, int x) {
    if (stack->size == stack->cap) {
        stack->data = realloc(stack->data, 2 * stack->cap * sizeof(int));
        stack->cap *= 2;
    }
    stack->data[stack->size] = x;
    ++stack->size;
}

int top(Typestack* stack) {
    return stack->data[stack->size - 1];
}

int pop(Typestack* stack) {
    int val = top(stack);
    stack->size--;
    return val;
}

signed main() {
    Typestack*  stack;

    stack = stack_init();

    for (; 0 == 0; ) {
        char* cmd;
        scanf("%ms", &cmd);

        // обработка команд
        if (strcmp(cmd, "END") == 0) {
            free(cmd);
            printf("%d\n", top(stack));
            clean(stack);
            return 0;
        }

        if (strcmp(cmd, "CONST") == 0) {
            int x;
            scanf("%d", &x);
            push(stack, x);
        }

        if (strcmp(cmd, "ADD") == 0) {
            int a = pop(stack);
            int b = pop(stack);
            push(stack, a + b);
        }

        if (strcmp(cmd, "SUB") == 0) {
            int a = pop(stack);
            int b = pop(stack);
            push(stack, a - b);
        }

        if (strcmp(cmd, "MUL") == 0) {
            int a = pop(stack);
            int b = pop(stack);
            push(stack, a * b);
        }

        if (strcmp(cmd, "DIV") == 0) {
            int a = pop(stack);
            int b = pop(stack);
            push(stack, a / b);
        }

        if (strcmp(cmd, "MAX") == 0) {
            int a = pop(stack);
            int b = pop(stack);
            push(stack, a > b ? a : b);
        }

        if (strcmp(cmd, "MIN") == 0) {
            int a = pop(stack);
            int b = pop(stack);
            push(stack, a < b ? a : b);
        }

        if (strcmp(cmd, "NEG") == 0) {
            int a = pop(stack);
            push(stack, -a);
        }

        if (strcmp(cmd, "DUP") == 0) {
            push(stack, top(stack));
        }

        if (strcmp(cmd, "SWAP") == 0) {
            int a = pop(stack);
            int b = pop(stack);
            push(stack, a);
            push(stack, b);
        }

        free(cmd);
    }

    printf("%d\n", top(stack));
    clean(stack);

    return 0;
}
