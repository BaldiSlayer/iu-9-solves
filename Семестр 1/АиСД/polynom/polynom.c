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

typedef long long ll;

struct pair {
    // first, second
    ll f, s;
};

struct pair gorner(ll n, ll *a, ll x) {
    struct pair ans = {0, 0};
    for (ll i = 0; i <= n; ++i) {
        ans.f = ans.f * x + a[i];
        ans.s = ans.s * x + a[i]*(n - i);
    }
    return ans;
}

int main() {
    ll n, x;
    scanf("%lld%lld", &n, &x);
    ll a[n+1];
    for (ll i = 0; i <= n; ++i) {
        scanf("%lld", &a[i]);
    }
    struct pair answer = gorner(n, a, x);
    printf("%lld\n%lld", answer.f, answer.s);

    return 0;
}
