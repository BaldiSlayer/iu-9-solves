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

int get(unsigned int * sieve, int i) {
    return ((sieve[i >> 5] >> (i & 31)) & 1);
}

void set0(unsigned int * sieve, int i) {
    sieve[i >> 5] &= ~(1u << (i & 31));
}

int main() {
    long long n;
    scanf("%lld", &n);

    if (n < 0) {
        n = -n;
    }

    int prime = 1;
    for (size_t i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            prime = 0;
            break;
        }
    }

    if (prime) {
        printf("%ld\n", n);
        return 0;
    }

    long long ans = 1;

    // строим решето Эратосфена
    long long sieve_size = n / 2 + 1;

    unsigned int* sieve = malloc((unsigned long long)((sieve_size / 32 + 1) * sizeof(unsigned int)));
    memset(sieve, -1, (unsigned long long)((sieve_size / 32 + 1) * sizeof(unsigned int)));

    for (long long i = 2; i < sieve_size; ++i) {
        if (get(sieve, i)) {
            if (n % i == 0) {
                ans = i;
            }

            if (i*i > n) {
                continue;
            }

            for (long long j = 1ll * i * i; j < sieve_size; j += i) {
                set0(sieve, j);
            }
        }
    }

    printf("%ld\n", ans);

    free(sieve);

    return 0;
}
