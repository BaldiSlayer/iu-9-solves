#pragma GCC optimize("unroll-loops", "O3")

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF 1000000228

int max(int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
}

int n = 1;
int* tree;

void build(int* a, int q) {
    while (n < q) {
        n *= 2;
    }

    tree = (int*)malloc(n * 2 * sizeof(int));
    memset(tree, -INF, 2 * n);

    for (int i = n; i < n + q; ++i) {
        tree[i] = a[i - n];
    }

    for (int i = n - 1; i >= 1; --i) {
        tree[i] = max(tree[2 * i], tree[2 * i + 1]);
    }
}

void set(int i, int v) {
    i += n;
    tree[i] = v;
    i /= 2;
    while (i >= 1) {
        tree[i] = max(tree[2 * i], tree[2 * i + 1]);
        i /= 2;
    }
}

int get(int l, int r) {
    int mx = -INF;
    for (l += n, r += n; l <= r; l /= 2, r /= 2) {
        if (l % 2 == 1) mx = max(mx, tree[l++]);
        if (r % 2 == 0) mx = max(mx, tree[r--]);
    }
    return mx;
}

int main() {
    int q;
    scanf("%d", &q);
    int* a = (int*)malloc(q * sizeof(int));

    for (int i = 0; i < q; ++i) {
        scanf("%d", &a[i]);
    }

    build(a, q);

    int m;
    scanf("%d", &m);

    int l, r;
    for (; m--;) {
        char* op;
        scanf("%ms", &op);
        scanf("%d%d", &l, &r);
        if (op[0] == 'M') {
            printf("%d\n", get(l, r));
        }
        else {
            set(l, r);
        }
        free(op);
    }


    free(tree);
    free(a);


    return 0;
}
