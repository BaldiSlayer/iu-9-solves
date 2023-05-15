#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cmath>

using namespace std;

typedef long double ld;

void init_dsu(vector<int> &p, vector<int> &rk) {
    for (int i = 0; i < p.size(); i++) {
        p[i] = i;
        rk[i] = 1;
    }
}

int get_root(int v, vector<int>& p, vector<int>& rk) {
    if (p[v] == v) {
        return v;
    }
    else {
        return p[v] = get_root(p[v], p, rk);
    }
}

int merge(int a, int b, vector<int>& p, vector<int>& rk) {
    int ra = get_root(a, p, rk), rb = get_root(b, p, rk);

    if (ra == rb) {
        return false;
    }
    else {
        if (rk[ra] < rk[rb]) {
            p[ra] = rb;
        }
        else if (rk[rb] < rk[ra]) {
            p[rb] = ra;
        }
        else {
            p[ra] = rb;
            rk[rb]++;
        }

        return true;
    }
}

//Тип для представления рёбер.
struct edge {
    int a, b;
    ld len;

    bool operator<(const edge& other) {
        return (len < other.len);
    }
};

signed main() {
    int n;
    cin >> n;
    vector<edge> edges;

    vector<int> p(n);
    vector<int> rk(n);

    // читаем координаты
    vector<pair<int, int>> coords(n);
    for (int i = 0; i < n; ++i) {
        cin >> coords[i].first >> coords[i].second;
    }

    for (int i = 0; i < n-1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            edges.push_back({i, j, 
                sqrtl((coords[i].first - coords[j].first) * (coords[i].first - coords[j].first)  + 
                (coords[i].second - coords[j].second) * (coords[i].second - coords[j].second))});
        }
    }

    sort(edges.begin(), edges.end());

    ld mst_weight = 0;

    init_dsu(p, rk);

    for (edge e : edges) {
        if (merge(e.a, e.b, p, rk)) {
            mst_weight += e.len;
        }
    }

    cout << fixed << setprecision(2) << mst_weight;

    return 0;
}