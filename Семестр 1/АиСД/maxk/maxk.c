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

int main() {
    int n;
    scanf("%d", &n);
    int* a = malloc(n * sizeof(int));
    for (size_t i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }

    int k;
    scanf("%d", &k);

    long long ans = 0;
    for (int i = 0; i < k; ++i) {
        ans += a[i];
    }

    long long cur = ans;
    for (int i = 0; i < n - k; ++i) {
        cur -= a[i];
        cur += a[i + k];
        if (cur > ans) {
            ans = cur;
        }
    }

    printf("%lld\n", ans);
    free(a);

    return 0;
}
