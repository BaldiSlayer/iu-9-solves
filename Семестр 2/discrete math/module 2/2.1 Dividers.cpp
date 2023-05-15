#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

void divs(vector<ll> &a, ll n) {
    for (ll i = 1; i * i <= n; ++i) {
        if (n % i == 0) {
            a.push_back(i);
            if (i != n / i) {
                a.push_back(n / i);
            }
        }
    }

    sort(a.begin(), a.end());
}

signed main() {
    ll x;
    cin >> x;

    if (x==1){
cout << "graph {\n1\n} ";
    return 0;
}

    vector<ll> dividers;
    divs(dividers, x);

    vector<pair<ll, ll>> graph;
    for (ll i = 0; i < dividers.size() - 1; ++i) {
        for (ll j = i + 1; j < dividers.size(); ++j) {
            if (dividers[j] % dividers[i] == 0) {
                ll flag = 0;
                for (ll k = i + 1; k < j; ++k) {
                    flag = ((dividers[j] % dividers[k] == 0) && (dividers[k] % dividers[i] == 0));
                    if (flag) {
                        break;
                    }
                }

                if (!flag) {
                    graph.push_back({dividers[i], dividers[j]});
                }
            }
        }
    }

    cout << "graph {\n";
    for (auto i : graph) {
        cout << i.first << " -- " << i.second << "\n";
    }
    cout << "}";

    return 0;
}