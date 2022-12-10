/*
  _     _                      ___  _      _                     _____ _   _  _____        __   __  ______
| |   (_)                    / _ \| |    | |                   |_   _| | | ||  _  |      /  | /  | | ___ \
| |    _ ___  _____      __ / /_\ \ | ___| | _____  ___ _   _    | | | | | || |_| |______`| | `| | | |_/ /
| |   | / __|/ _ \ \ /\ / / |  _  | |/ _ \ |/ / __|/ _ \ | | |   | | | | | |\____ |______|| |  | | | ___ \
| |___| \__ \ (_) \ V  V /  | | | | |  __/   <\__ \  __/ |_| |  _| |_| |_| |.___/ /      _| |__| |_| |_/ /
\_____/_|___/\___/ \_/\_/   \_| |_/_|\___|_|\_\___/\___|\__, |  \___/ \___/ \____/       \___/\___/\____/
                                                         __/ |
                                                        |___/
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 1000001

// дерево Фенвика
int* fenwick;

// get ans
int get(int i) {
    int res = 0;
    for (; i > 0; i -= i & -i) {
        res ^= fenwick[i];
    }
    return res;
}

int query(int l, int r) {
    return get(r) ^ get(l-1);
}

void update(int n, int i, int x) {
    for (; i <= n; i += i & -i) {
        fenwick[i] ^= x;
    }
}

// make fenwick tree O(NlogN), TODO to O(n)
/*void tree_make(int n, char* arr) {
    fenwick = calloc((size_t)(n + 1), sizeof(int));
    for (int i = 0; i < n; ++i) {
        update(n, i + 1, (1 << (arr[i] - 'a')));
    }
}*/

void tree_make2(int n, char* a) {
    fenwick = calloc((size_t) (n + 1), sizeof(int));

    for (int i = 1; i <= n; i++) {
        fenwick[i] ^= (1 << (a[i - 1] - 'a'));
        if (i + (i & -i) <= n)
            fenwick[i + (i & -i)] ^= fenwick[i];
    }

}

signed main() {
    char str[MAX_N], s[MAX_N];
    scanf("%s", &str[0]);
    int n = (int)strlen(str);

    tree_make2(n, str);

    int m, ind;
    scanf("%d", &m);

    char op[4];
    for (; m--; ) {
        scanf("%s", &op[0]);
        if (op[0] == 'H') {
            // если это проверка
            int l, r;
            scanf("%d%d", &l, &r);
            int ans = query(l + 1, r + 1);
            if ((r - l + 1) & 1) {
                printf((ans & (ans - 1)) ? "NO\n" : "YES\n");
            } else {
                printf(ans ? "NO\n" : "YES\n");
            }
        }
        else {
            scanf("%d%s", &ind, &s[0]);

            // апдейтим всю строку
            int len = (int)strlen(s);
            for (int j = ind; j < ind + len; ++j) {
                update(n, j + 1, (1 << (str[j] - 'a')) ^ (1 << (s[j - ind] - 'a')));
            }
            memcpy(&str[ind], s, (size_t)len);
        }
    }

    free(fenwick);

    return 0;
}
