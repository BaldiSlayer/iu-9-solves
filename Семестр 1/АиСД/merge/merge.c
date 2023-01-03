#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int k, v, ind;
} Node;

typedef struct {
    Node** heap;
    int cap;
    int count;
} Queue;

Queue* q;

signed main() {
    int k;
    scanf("%d", &k);
    int numOfElements = 0, sizes[k], *arrs[k];
    for (int i = 0; i < k; ++i) {
        scanf("%d", &sizes[i]);
        arrs[i] = malloc(sizes[i] * sizeof(int));
        numOfElements += (int)sizes[i];
    }

    q = malloc(sizeof(Queue));
    q->cap = numOfElements;
    q->count = 0;
    q->heap = calloc(numOfElements, sizeof(Node*));

    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < sizes[i]; ++j) {
            scanf("%d", &arrs[i][j]);
        }
    }

    int indexes[k];
    for (int i = 0; i < k; ++i) {
        int key = -arrs[i][0], value = i;
        int i = q->count;
        ++q->count;
        Node* new = malloc(sizeof(Node));
        q->heap[i] = new;
        new->ind = i;
        new->k = key;
        new->v = value;
        for (; i > 0 && q->heap[(i - 1) / 2]->k < key; q->heap[i]->ind = i, i = (i - 1) / 2) {
            Node *temp = q->heap[(i - 1) / 2];
            q->heap[(i - 1) / 2] = q->heap[i];
            q->heap[i] = temp;
        }
        q->heap[i]->ind = i;
        indexes[i] = 1;
    }

    for (int i = 0; i < numOfElements; ++i) {
        Node* v = q->heap[0];
        --q->count;
        if (q->count > 0) {
            q->heap[0] = q->heap[q->count];
            q->heap[0]->ind = 0;
            int i = 0, top;
            for (top = -200; i != top;) {
                top = i;
                int left_child = i * 2 + 1, right_child = i * 2 + 2;

                if (left_child < q->count && q->heap[left_child]->k > q->heap[i]->k) {
                    i = left_child;
                }
                if (right_child < q->count && q->heap[right_child]->k > q->heap[i]->k) {
                    i = right_child;
                }

                Node *temp = q->heap[i];
                q->heap[i] = q->heap[top];
                q->heap[top] = temp;

                q->heap[i]->ind = i;
                q->heap[top]->ind = top;
            }
        }

        printf("%d ", -v->k);
        int index = v->v;
        if (indexes[index] < sizes[index]) {
            int key = -arrs[index][indexes[index]], value = index;
            int i = q->count;
            ++q->count;
            Node* new = malloc(sizeof(Node));
            q->heap[i] = new;
            new->ind = i;
            new->k = key;
            new->v = value;
            for (; i > 0 && q->heap[(i - 1) / 2]->k < key; q->heap[i]->ind = i, i = (i - 1) / 2) {
                Node *temp = q->heap[(i - 1) / 2];
                q->heap[(i - 1) / 2] = q->heap[i];
                q->heap[i] = temp;
            }

            q->heap[i]->ind = i;

            indexes[index]++;
        }
        free(v);
    }

    for (int i = 0; i < q->count; ++i) {
        free(q->heap[i]);
    }

    free(q->heap);
    free(q);

    for (int i = 0; i < k; ++i) {
        free(arrs[i]);
    }

    return 0;
}
