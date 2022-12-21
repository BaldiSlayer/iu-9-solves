#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int low, high;
} task;

typedef struct {
    task* data;
    unsigned int cap;
    unsigned int size;
} Typestack;

Typestack* stack;
int n;
int* a;

void stack_init() {
    stack = (Typestack*)malloc(sizeof(Typestack));
    stack->cap = 10;
    stack->size = 0;
    stack->data = malloc(10 * sizeof(task));
}

void clean() {
    free(stack->data);
    free(stack);
}

void push(int l, int r) {
    if (stack->size == stack->cap) {
        stack->data = realloc(stack->data, 2 * stack->cap * sizeof(task));
        stack->cap *= 2;
    }
    stack->data[stack->size].low = l;
    stack->data[stack->size].high = r;
    ++stack->size;
}

task top() {
    return stack->data[stack->size - 1];
}

task pop() {
    task val = top();
    stack->size--;
    return val;
}

int partition(int low, int high) {
    int x = a[high - 1], i = low, temp;
    for (int j = low; j < high - 1; ++j) {
        if (a[j] < x) {
            temp = a[i];
            a[i] = a[j];
            a[j] = temp;

            ++i;
        }
    }

    temp = a[i];
    a[i] = a[high-1];
    a[high-1] = temp;

    return i;
}


void solve() {
    // инициализация стека
    stack_init();

    // сортировка массива
    push(0, n);
    while (stack->size) {
        int low = top().low, high = pop().high;

        if (low < high - 1) {
            int m = partition(low, high);
            push(  low, m);
            push(m + 1, high);
        }
    }

    // вывод ответа
    for (int i = 0; i < n; ++i) {
        printf("%d ", a[i]);
    }

    // очиска стека
    clean();
}

signed main() {
    scanf("%d", &n);

    a = (int*)malloc(n * sizeof(int));

    for (size_t i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }

    solve(n);

    free(a);

    return 0;
}
