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

int* fenwick;
char* peak;
int* a;
int n;

int sum(int i) {
    int sum = 0;
    for (; i > 0; i -= i & -i) {
        sum += fenwick[i];
    }
    return sum;
}

void update(int ind, int dif) {
    for (int i = ind; i <= n; i += i & -i) {
        fenwick[i] += dif;
    }
}

int get_sum(int l, int r) {
    return sum(r) - sum(l-1);
}

void tree_build() {
    fenwick = calloc((size_t)n+1, sizeof(int));
    for (int i = 1; i <= n; ++i) {
        fenwick[i] += peak[i-1];
        if (i + (i & -i) <= n) {
            fenwick[i + (i & -i)] += fenwick[i];
        }
    }
}

void check_for_updates(int i) {
    if (i < 0) {
        return;
    }
    if (i >= n) {
        return;
    }

    int is_now_peak = ((i == 0 || a[i - 1] <= a[i]) && (i == n - 1 || a[i + 1] <= a[i]));
    if (is_now_peak != peak[i]) {
        update(i + 1, is_now_peak - peak[i]);
        peak[i] = is_now_peak;
    }
}

int main() {
    scanf("%d", &n);

    a = malloc(n * sizeof(int));
    peak = calloc(n, sizeof(char));

    for (unsigned int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }

    for (int i = 0; i < n; ++i) {
        if ((i == 0 || a[i - 1] <= a[i]) && (i == n - 1 || a[i + 1] <= a[i])) {
            peak[i] = 1;
        }
    }

    // строим дерево Фенвика за O(n)
    tree_build();

    /*for (int i = 0; i <=n; ++i) {
        printf("%d ", fenwick[i]);
    }*/

    int l, r;
    char* type;
    scanf("%ms", &type);
    for ( ; type[0] != 'E'; ) {
        // обрабатываем запросы
        if (type[0] == 'P') {
            scanf("%d%d", &l, &r);

            if (r == 2) {
                int hui = 0;

            }

            printf("%d\n", get_sum(l + 1, r + 1));
        }
        else if (type[0] == 'U') {
            scanf("%d%d", &l, &r);
            a[l] = r;
            // заметим, что изменение элемента с индексом i затронет только элементы с индексами (i-1), i, (i+1)
            check_for_updates(l);
            check_for_updates(l-1);
            check_for_updates(l+1);
        }

        free(type);
        scanf("%ms", &type);
    }

    // освобождаем всю занятую память
    free(type);
    free(a);
    free(peak);
    free(fenwick);

    return 0;
}
