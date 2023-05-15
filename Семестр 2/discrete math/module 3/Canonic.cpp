#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Automat {
	int n, m, q0;
	vector<vector<int>> moves;
	vector<vector<string>> outs;

	Automat() {
		Input();
	}

	Automat(int n_, int m_, int q0_) {
		this->n = n_;
		this->m = m_;
		this->q0 = q0_;
		this->moves.resize(this->n, vector<int>(this->m));
		this->outs.resize(this->n, vector<string>(this->m));
	}


	void Canonize() {
		vector<int> used(n, -1);
		int timer = 0;

		Automat b(this->n, this->m, this->q0);

		// выполняем обход в глубину
		DFS(q0, timer, used);

		for (int i = 0; i < n; ++i) {
			if (used[i] != -1) {
				// значит надо перенумеровать

				b.outs[used[i]] = this->outs[i];
				for (int j = 0; j < m; ++j) {
					b.moves[used[i]][j] = used[this->moves[i][j]];
				}
			}
		}
		b.q0 = used[this->q0]; // 0
		b.Print();
	}


	void DFS(int v, int &t, vector<int> &used) {
		used[v] = t++;

		for (int i = 0; i < m; ++i) {
			if (used[this->moves[v][i]] == -1) {
				DFS(this->moves[v][i], t, used);
			}
		}
	}

	void Input() {
		cin >> n >> m >> q0;

		moves.resize(n, vector<int>(m));
		for (auto& i : moves) {
			for (auto& j : i) {
				cin >> j;
			}
		}

		outs.resize(n, vector<string>(m));
		for (auto& i : outs) {
			for (auto& j : i) {
				cin >> j;
			}
		}
	}

	void Print() {
		cout << n << "\n" << m << "\n" << q0 << "\n";

		for (auto i : moves) {
			for (auto j : i) {
				cout << j << " ";
			}
			cout << "\n";
		}

		for (auto i : outs) {
			for (auto j : i) {
				cout << j << " ";
			}
			cout << "\n";
		}
	}
};

signed main() {
	Automat a;
	a.Canonize();

	return 0;
}