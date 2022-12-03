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

long long gorner(unsigned int n, long long* a, long long x) {
    long long ans = 0;
    for (unsigned int i = 0; i <= n; ++i) {
        ans = ans * x + a[i];
    }
    return ans;
}

long long gorner_from_derivative(unsigned int n, long long* a, long long x) {
    long long ans = 0;
    for (unsigned int i = 0; i < n; ++i) {
        ans = ans * x + a[i] * (n - i);
    }
    return ans;
}

signed main() {
    long long n, x;
    scanf("%lld%lld", &n, &x);
    long long a[n + 1];
    for (size_t i = 0; i <= n; ++i) {
        scanf("%lld", &a[i]);
    }

    printf("%lld\n%lld\n", gorner(n, a, x), gorner_from_derivative(n, a, x));
    return 0;
}
