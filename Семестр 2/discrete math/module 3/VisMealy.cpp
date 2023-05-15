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

	void VisMealy() {
		cout << "digraph {\n\trankdir = LR\n";

		for (int i = 0; i < this->n; ++i) {
			for (int j = 0; j < this->m; ++j) {
				cout << "\t" << i << " -> " << this->moves[i][j] << " [label = \"" 
					<< (char)(j + 97) << "(" << this->outs[i][j] << ")" << "\"]\n";
			}
		}

		cout << "}";
	}
};

signed main() {
	Automat a;
	a.VisMealy();

	return 0;
}