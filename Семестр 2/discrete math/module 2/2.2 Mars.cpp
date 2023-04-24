#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

bool DFS(vector<vector<int>>& graph, vector<pair<set<int>, set<int>>>& comps,
	vector<int>& colors, int v, int c) {
	colors[v] = c;
	if (c == 1) {
		comps[comps.size() - 1].first.insert(v);
	}
	else {
		comps[comps.size() - 1].second.insert(v);
	}

	for (auto to : graph[v]) {
		// если образовался "цикл"
		if (colors[v] == colors[to]) {
			return true;
		}

		if (!colors[to]) {
			bool cycle = DFS(graph, comps, colors, to, (c == 1 ? 2 : 1));
			if (cycle) {
				return true;
			}
		}
	}

	return false;
}

signed main() {
	ios_base::sync_with_stdio(0); cin.tie(0);

	int n;
	cin >> n;

	// обеспечение того, что мы будем идти по ребрам в лексикографическом порядке
	vector<vector<int>> graph(n);

	char ch;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cin >> ch;

			if (j <= i && ch == '+') {
				graph[i].push_back(j);
				graph[j].push_back(i);
			}
		}
	}

	// раскрасим граф в два цвета
	vector<int> colors(n, 0);
	vector<pair<set<int>, set<int>>> comps;
	for (int i = 0; i < n; ++i) {
		if (!colors[i]) {
			comps.push_back({});
			if (DFS(graph, comps, colors, i, 1)) {
				cout << "No solution";
				return 0;
			}
		}
	}

	// рюкзак

	vector<vector<int>> dp(comps.size() + 1, vector<int>(n / 2 + 1, 0));
	vector<vector<int>> reversed(comps.size() + 1, vector<int>(n / 2 + 1, 0));

	dp[0][0] = true;
	for (int i = 1; i <= comps.size(); ++i) {
		for (int j = 0; j <= n / 2; ++j) {
			if (j - (int)comps[i - 1].first.size() >= 0 && dp[i - 1][j - comps[i - 1].first.size()]) {
				dp[i][j] = true;
				reversed[i][j] = false;
			}

			if (j - (int)comps[i - 1].second.size() >= 0 && dp[i - 1][j - comps[i - 1].second.size()]) {
				reversed[i][j] = !dp[i][j];

				// проверяем нужно ли переворачивать
				// .first всегда лексикографически меньше, чем .second
				if (!reversed[i][j]) {
					if (reversed[i - 1][j - comps[i - 1].first.size()] &&
						!reversed[i - 1][j - comps[i - 1].second.size()]) {
						reversed[i][j] = true;
					}
				}

				dp[i][j] = true;				
			}
		}
	}

	// восстанавливаем ответ
	// ищем наиболее привлекательное число участников в команде
	int cur = -1;
	for (int j = n / 2; j > 0; --j) {
		if (dp[comps.size()][j]) {
			cur = j;
			break;
		}
	}

	if (cur == -1) {
		cout << "No solution";
		return 0;
	}

	vector<int> ans;
	for (int i = comps.size(); i > 0; --i) {
		if (reversed[i][cur]) {
			for (auto i : comps[i - 1].second) {
				ans.push_back(i + 1);
			}
			cur -= comps[i - 1].second.size();
		}
		else {
			for (auto i : comps[i - 1].first) {
				ans.push_back(i + 1);
			}
			cur -= comps[i - 1].first.size();
		}
	}

	sort(ans.begin(), ans.end());

	for (auto i : ans) {
		cout << i << " ";
	}

	return 0;
}