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
#include <stdbool.h>

const int N = 8;

bool solve(int* a, int* b) {
    for (int i = 0; i < N; ++i) {
        bool is_found = false;
        for (int j = 0; j < N; ++j) {
            if (a[i] == b[j]) {
                // TODO
                // если решение не будет заходить - поменять на INTMAX
                b[j] = 1e9 + 228;
                is_found = true;
                break;
            }
        }
        if (!is_found) {
            return false;
        }
    }
    return true;
}

int main() {
    int a[N], b[N];
    for (int i = 0; i < N; ++i) {
        scanf("%d", &a[i]);
    }
    for (int i = 0; i < N; ++i) {
        scanf("%d", &b[i]);
    }
    if (solve(a, b)) {
        printf("yes");
    } else {
        printf("no");
    }
    return 0;
}
