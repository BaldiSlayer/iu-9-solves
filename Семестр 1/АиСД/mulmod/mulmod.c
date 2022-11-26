// _     _                      ___  _      _                     _____ _   _  _____        __   __  ______
//| |   (_)                    / _ \| |    | |                   |_   _| | | ||  _  |      /  | /  | | ___ \
//| |    _ ___  _____      __ / /_\ \ | ___| | _____  ___ _   _    | | | | | || |_| |______`| | `| | | |_/ /
//| |   | / __|/ _ \ \ /\ / / |  _  | |/ _ \ |/ / __|/ _ \ | | |   | | | | | |\____ |______|| |  | | | ___ \
//| |___| \__ \ (_) \ V  V /  | | | | |  __/   <\__ \  __/ |_| |  _| |_| |_| |.___/ /      _| |__| |_| |_/ /
//\_____/_|___/\___/ \_/\_/   \_| |_/_|\___|_|\_\___/\___|\__, |  \___/ \___/ \____/       \___/\___/\____/
//                                                         __/ |
//                                                        |___/

#include <stdio.h>

typedef unsigned long ul;
typedef unsigned long long ull;

ul modulo_multiplying(ul a, ul b, ul m) {
    ul ans = 0;
    for (ull mask = 1llu << 63; mask > 0; mask >>= 1) {
        ans = ans * 2 % m + (mask & a ? 1lu : 0lu) * (b % m);
        ans %= m;
    }
    return ans;
}

int main() {
    ul a, b, m;
    scanf("%lu%lu%lu", &a, &b, &m);
    printf("%lu", modulo_multiplying(a, b, m));
    return 0;
}
