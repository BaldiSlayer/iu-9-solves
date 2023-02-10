#include <iostream>
#include <vector>
#include <algorithm>

typedef long long ll;

#define INF (1e9 + 228)

using namespace std;

signed main() {
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
