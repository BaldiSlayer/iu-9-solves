#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

struct Component {
	vector<int> p;
	long long edges_cnt;

	bool operator<(const Component& other) {
		if (this->p.size() < other.p.size()) {
			return true;
		}

		if (this->p.size() == other.p.size() && this->edges_cnt < other.edges_cnt) {
			return true;
		}

		if (this->p.size() == other.p.size() && this->edges_cnt == other.edges_cnt) {
			for (int i = 0; i < other.p.size(); ++i) {
				if (this->p[i] > other.p[0]) {
					return true;
				}

				if (this->p[i] < other.p[0]) {
					return false;
				}
			}
		}

		return false;
	}
};

void DFS(vector<vector<int>> &graph, vector<int> &used, int v, int c, 
	vector<int> &comp) {
	used[v] = c;

	for (auto to : graph[v]) {
		if (!used[to]) {
			DFS(graph, used, to, c, comp);
		}
	}

	comp.push_back(v);
}

signed main() {
	int n, m;
	cin >> n >> m;

	vector<vector<int>> graph(n);
	vector<pair<int, int>> edges;
	for (int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
		edges.push_back({a, b});
	}

	vector<int> used(n, 0);
	int c = 1;


	Component max_comp;
	max_comp.edges_cnt = 0;

	for (int i = 0; i < n; ++i) {
		if (!used[i]) {
			Component now;
			DFS(graph, used, i, c, now.p);

			sort(now.p.begin(), now.p.end());

			long long e = 0;
			for (auto u : now.p) {
				e += graph[u].size();
			}
			now.edges_cnt = e / 2;

			if (!(now < max_comp)) {
				max_comp = now;
			}
		}
		++c;
	}

	// вывод
	cout << "graph {\n";

	// вершины
	for (int i = 0; i < n; ++i) {
		cout << "\t";
		cout << i << " ";
		if (find(max_comp.p.begin(), max_comp.p.end(), i) != max_comp.p.end()) {
			cout << "[color = red]";
		}
		cout << "\n";
	}

	// ребра
	for (auto i : edges) {
		cout << "\t";
		cout << i.first << " -- " << i.second << " ";
		if (find(max_comp.p.begin(), max_comp.p.end(), i.first) != max_comp.p.end()) {
			cout << "[color = red]";
		}
		cout << "\n";
	}

	cout << "}";
		
	return 0;
}