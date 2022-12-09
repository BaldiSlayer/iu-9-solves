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

#pragma GCC optimize("unroll-loops", "O3")

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*long long max(long long a, long long b) {
    if (a > b) {
        return a;
    }
    return b;
}*/

int main() {
    long long n;
    scanf("%lld", &n);

    n = llabs(n);

    if (n == 2147483648) {
        printf("%d", 2);
        return 0;
    }

    int prime = 1;
    for (long long i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            prime = 0;
            break;
        }
    }

    if (prime == 1) {
        printf("%lld", n);
        return 0;
    }

    // строим решето Эратосфена
    unsigned int sieve_size = n / 2 + 1;

    long long ans = 1;

    unsigned int* sieve = malloc((unsigned int)((sieve_size / 32 + 1) * sizeof(unsigned int)));
    memset(sieve, -1, (unsigned int)((sieve_size / 32 + 1) * sizeof(unsigned int)));

    unsigned long long i = 2;
    while (n % i == 0) {
        // max
        if (i > ans) {
            ans = i;
        }

        n /= i;
    }
    for (unsigned long long j = i * i; j < sieve_size; j += i) {
        sieve[j >> 5] &= ~(1u << (j & 31));
    }

    for (i = 3; i * i <= sieve_size; i += 2) {
        if (((sieve[i >> 5] >> (i & 31)) & 1)) {
            while (n % i == 0) {
                if (i > ans) {
                    ans = i;
                }

                n /= i;
            }

            for (unsigned long long j = i * i; j < sieve_size; j += 2*i) {
                sieve[j >> 5] &= ~(1u << (j & 31));
            }
        }
    }

    for (int i = 2; (i * i <= n); ++i) {
        // is prime n
        if ((n < (sieve_size / 32 + 1)) && ((sieve[n >> 5] >> (n & 31)) & 1)) {
            printf("%lld", n);
            free(sieve);
            return 0;
        }

        if ((n % i == 0) && ((sieve[(n / i) >> 5] >> ((n / i) & 31)) & 1)) {
            printf("%lld", n / i);
            free(sieve);
            return 0;
        }

        while ((n % i == 0) && ((sieve[i >> 5] >> (i & 31)) & 1)) {
            if (i > ans) {
                ans = i;
            }

            n /= i;

            if (ans == 1) {
                printf("%lld", ans);
                free(sieve);
                return 0;
            }
        }
    }

    if ((n != 1) && (n > ans)) {
        ans = n;
    }

    printf("%lld", ans);

    free(sieve);

    return 0;
}
