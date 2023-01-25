#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

typedef struct {
    ll k, v;
} pair;

typedef struct {
    pair* pairs;
    int top, cap;
} DinamickArray;

// хэш функция, TODO обработать коллизии
int h(int i) {
    int m = 100000;
    return abs(i) % m;
}

pair* DinamickArraySearch(DinamickArray* v, int k) {
    for (int i = 0; i < v->top; ++i) {
        if (k == v->pairs[i].k) {
            return &v->pairs[i];
        }
    }
    return NULL;
}

int Get(DinamickArray* DispArray, int i) {
    pair* v = DinamickArraySearch(&DispArray[h(i)], i);
    return (v ? v->v : -1);
}

void Insert(DinamickArray* DispArray, int i, int v) {
    DinamickArray* arr = &DispArray[h(i)];
    pair* node = DinamickArraySearch(arr, i);
    if (!node) {
        if (arr->cap == arr->top) {
            arr->pairs = realloc(arr->pairs, (++arr->cap) * sizeof(pair));
        }
        arr->pairs[arr->top].k = i;
        arr->pairs[arr->top++].v = v;
    }
    else {
        node->v = v;
    }
}

signed main() {
    int m = 100000;

    DinamickArray* DispArray;

    int n;
    scanf("%d", &n);

    // DispArr init
    DispArray = malloc(m * sizeof(DinamickArray));
    for (int i = 0; i < m; i++) {
        DispArray[i].cap = 1;
        DispArray[i].top = 0;
        DispArray[i].pairs = calloc(DispArray[i].cap, sizeof(pair));
    }


    int xor = 0, *count = calloc(n, sizeof(int)), num;
    ll ans = 0;
    for (int i = 0; i < n; ++i) {
        scanf("%d", &num);
        xor ^= num;

        if (i == 0) {
            if (!num) {
                count[0] = 1;
                ans++;
            }
            Insert(DispArray, xor, 0);
        }
        else {
            long long ind = Get(DispArray, xor);
            if (ind != -1) {
                count[i] = count[ind] + 1;
            }
            if (xor == 0 && count[i] == 0) {
                ++count[i];
            }
            Insert(DispArray, xor, i);
            ans += count[i];
        }
    }

    printf("%lld\n", ans);

    // Clean
    for (int i = 0; i < m; ++i) {
        free(DispArray[i].pairs);
    }

    free(count);
    free(DispArray);

    return 0;
}
