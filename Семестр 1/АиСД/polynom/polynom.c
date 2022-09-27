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
