#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

void dfs(set<pair<int, int>> &ans, vector<vector<int>>& g, vector<int> &used,
    vector<int> &d, vector<int> &h, int v, int p = -1) {
    used[v] = true;
    d[v] = h[v] = (p == -1 ? 0 : h[p] + 1);
    for (int u : g[v]) {
        if (u != p) {
            if (used[u]) {
                d[v] = min(d[v], h[u]);
            }
            else {
                dfs(ans, g, used, d, h, u, v);
                d[v] = min(d[v], d[u]);
                if (h[v] < d[u]) {
                    ans.insert({min(v, u), max(v, u)});
                }
            }
        }
    }
}

signed main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);

    vector<int> used(n), h(n), d(n);
    set<pair<int, int>> ans;

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            dfs(ans, g, used, d, h, i);
        }
    }

    cout << ans.size();

	return 0;
}