#pragma GCC optimize("unroll-loops", "O3")

#include <iostream>
#include <vector>

typedef long long ll;

using namespace std;

struct FenwickTree {
    vector<ll> f;
    int n;

    void init(int n_) {
        f.resize(n_, 0);
        n = n_;
    }

    void inc(int pos, int val) {
        for (int i = pos; i < n; i |= (i + 1)) {
            f[i] += val;
        }
    }

    ll sum(int pos) {
        ll res = 0;
        for (int i = pos; i >= 0; i = (i & (i + 1)) - 1) {
            res += f[i];
        }
        return res;
    }

    ll sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }
};

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int n, q;
    cin >> n >> q;

    FenwickTree f;
    f.init(n);
    vector<ll> a(n, 0);

    int type, l, r;
    for (; q--; ) {
        cin >> type >> l >> r;

        if (type == 1) {
            cout << f.sum(l - 1, r - 1) << "\n";
        }
        else {
            f.inc(l - 1, r - a[l - 1]);
            a[l - 1] = r;
        }
    }

    return 0;
}
