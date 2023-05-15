#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef long long ll;

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, int>>> graph(n);
    vector<int> used(n, 0);

    for (int i = 0; i < m; ++i) {
        int u, v, len;
        cin >> u >> v >> len;
        graph[u].push_back({v, len});
        graph[v].push_back({u, len});
    }


    ll mst_weight = 0ll;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
    q.push({ 0, 0 });

    while (!q.empty()) {
        pair<int, int> c = q.top();
        q.pop();

        int dst = c.first, v = c.second;

        if (used[v]) {
            continue;
        }

        used[v] = true;
        mst_weight += dst;

        for (pair<int, int> e : graph[v]) {
            int u = e.first, len_vu = e.second;

            if (!used[u]) {
                q.push({ len_vu, u });
            }
        }
    }

    cout << mst_weight;

    return 0;
}