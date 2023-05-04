#include <iostream>
#include <vector>
#include <algorithm>

typedef long long ll;

#define INF (1e9 + 228)

using namespace std;

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int n;
    cin >> n;

    vector<vector<int>> a(n, vector<int>(n));
    for (int i = 0;i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> a[i][j];
        }
    }

    vector<vector<ll>> dp(n + 2, vector<ll>(n+2, INF));

    dp[1][1] = a[0][0];

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (i == 1 && j == 1) {
                continue;
            }
            dp[i][j] = min(dp[i][j-1], dp[i-1][j]) + a[i-1][j-1];
        }
    }

    cout << dp[n][n];

    return 0;
}
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

typedef long long ll;

#define INF (1e9 + 228)

using namespace std;

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int n;
    cin >> n;

    vector<vector<int>> a(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> a[i][j];
        }
    }

    vector<pair<int, int>> go = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

    vector<vector<int>> d(n, vector<int>(n, INF));
    d[0][0] = a[0][0];
    set<pair<int, pair<int, int>>> q;
    q.insert({ a[0][0] , {0, 0} });

    while (!q.empty()) {
        // получаем координаты вершины
        pair<int, int> v = q.begin()->second;
        q.erase(q.begin());

        for (auto to : go) {
            pair<int, int> e = { v.first + to.first, v.second + to.second };
            if ((0 <= e.first && e.first < n) && (0 <= e.second && e.second < n)) {
                if (d[e.first][e.second] > d[v.first][v.second] + a[e.first][e.second]) {
                    q.erase({ d[e.first][e.second] , e});
                    d[e.first][e.second] = d[v.first][v.second] + a[e.first][e.second];
                    q.insert({ d[e.first][e.second] , e});
                }
            }
        }
    }

    cout << d[n - 1][n - 1];

    return 0;
}