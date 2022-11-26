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

const size_t FIB_SIZE = 94;

typedef unsigned long long ull;

int main() {
    unsigned long long x;
    scanf("%llu", &x);

    char ans[FIB_SIZE];
    if (x == 0) {
        ans[0] = '0';
        ans[1] = '\0';
        printf("%s", ans);
        return 0;
    }

    // precounting of Fibs
    ull fib[FIB_SIZE];
    fib[0] = 1; fib[1] = 2;
    for (size_t i = 2; i < FIB_SIZE; ++i) {
        fib[i] = fib[i - 2] + fib[i - 1];
    }

    int ind = 0;
    while (fib[ind + 1] <= x) {
        ++ind;
    }

    int max_index = ind;
    x -= fib[ind];
    ind--;
    ans[0] = '1';
    for (; ind >= 0; ind--) {
        if (fib[ind] <= x) {
            x -= fib[ind];
            ans[max_index - ind] = '1';
        } else {
            ans[max_index - ind] = '0';
        }
    }

    ans[max_index + 1] = '\0';
    printf("%s", ans);

    return 0;
}
