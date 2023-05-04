#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int low, high;
} Task;

typedef struct {
    Task* data;
int cap, top;
} TStack;

TStack* stack;

void InitStack() {
  stack = (TStack*)malloc(sizeof(TStack));
  stack->data = malloc(2 * sizeof(Task));
  stack->cap = 2;
  stack->top = 0;
}

void Assign(int low, int high) {
  stack->data[stack->top].low = low;
  stack->data[stack->top].high = high;
  stack->top++;
}

void Push(int low, int high) {
  if (stack->top == stack->cap) {
    stack->data = realloc(stack->data, (stack->cap + 1) * sizeof(Task));
    stack->cap++;
  }
  Assign(low, high);
}

Task Top() {
  return stack->data[stack->top - 1];
}

Task Pop() {
  Task a = Top();
  stack->top--;
  return a;
}

int Empty() {
  return stack->top == 0;
}

void CleanStack() {
  free(stack->data);
  free(stack);
}

void Swap(int* a, int i, int j) {
  int temp = a[i];
  a[i] = a[j];
  a[j] = temp;
}

int Partition(int* a, int l, int r)  {
  int v = a[(l + r) / 2];
  int i = l, j = r;
  while (i <= j) {
    while (a[i] < v) {
      i++;
    }
    while (a[j] > v) {
      j--;
    }
    if (i >= j) {
      break;
    }
    Swap(a, i++, j--);
  }
  return j;
}

void Sorting(int* a, int n) {
  //a[0] = 80;
  Push(0, n-1);
  while (!Empty()) {
    Task borders = Pop();
    if (borders.high <= borders.low) {
      continue;
    }
    int i = Partition(a, borders.low, borders.high);
    if (i - borders.low > borders.high - i) {
      Push(borders.low, i );
      Push(i + 1, borders.high);
    }
else {
      Push(i + 1, borders.high);
      Push(borders.low, i);
    }
  }
}

int main() {
  int n;
  scanf("%d", &n);

  int* a = malloc(n * sizeof(int));

  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
  }

  InitStack();
  Sorting(a, n);

  for (int i = 0; i < n; i++) {
    printf("%d ", a[i]);
  }

  CleanStack();
  free(a);

  return 0;
}