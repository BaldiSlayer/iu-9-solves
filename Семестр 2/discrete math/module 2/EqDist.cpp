#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

vector<int> BFS(vector<vector<int>> &g, int s) {
	vector<int> used(g.size(), 0), path(g.size(), 0);
	queue<int> q;
	q.push(s);

	while (!q.empty()) {
		int v = q.front();
		q.pop();

		for (auto to : g[v]) {
			if (!used[to]) {
				q.push(to);
				used[to] = 1;
				path[to] = path[v] + 1;
			}
		}
	}
	return path;
}

signed main() {
	int n, m;
	cin >> n >> m;
	vector<vector<int>> graph(n);

	for (int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	int k;
	cin >> k;
	vector<int> reference(k);

	for (auto& i : reference) {
		cin >> i;
	}

	// запускаем BFS
	vector<vector<int>> pathes;
	for (auto i : reference) {		
		pathes.push_back(BFS(graph, i));
	}

	vector<int> ans;
	// перебираем вершины
	for (int i = 0; i < n; ++i) {
		// если есть - то скип
		if (find(reference.begin(), reference.end(), i) != reference.end()) {
			continue;
		}

		int val = pathes[0][i];
		for (int j = 1; j < reference.size(); ++j) {
			if (val != pathes[j][i]) {
				val = -10;
				break;
			}
		}

		if (val == -10 || val == 0) {
			continue;
		}

		ans.push_back(i);
	}

	if (ans.size() == 0) {
		cout << "-";
		return 0;
	}

	sort(ans.begin(), ans.end());
	for (auto i : ans) {
		cout << i << " ";
	}

	return 0;
}