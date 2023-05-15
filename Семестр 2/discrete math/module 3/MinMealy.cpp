#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <algorithm>

using namespace std;

struct DSU {
    vector<int> p, rk;

    DSU(int n) {
        p.resize(n);
        rk.resize(n);
        for (int i = 0; i < n; i++) {
            p[i] = i;
            rk[i] = 1;
        }
    }

    int get_root(int v) {
        if (p[v] == v) {
            return v;
        }
        return p[v] = get_root(p[v]);
    }

    int merge(int a, int b) {
        int ra = get_root(a), rb = get_root(b);

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
};

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

    void Canonize() {        
        Automat b(this->n, this->m, this->q0); 

        vector<int> used(n, -1);
        int timer = 0;
        DFS(q0, timer, used);
        for (int i = 0; i < n; ++i) {
            if (used[i] != -1) {
                b.outs[used[i]] = this->outs[i];
                for (int j = 0; j < m; ++j) {
                    b.moves[used[i]][j] = used[this->moves[i][j]];
                }
            }
        }
        b.q0 = used[this->q0]; // 0

        *this = b;
    }


    void DFS(int v, int& t, vector<int>& used) {
        used[v] = t++;

        for (int i = 0; i < m; ++i) {
            if (used[this->moves[v][i]] == -1) {
                DFS(this->moves[v][i], t, used);
            }
        }
    }

    void Split1(int &m_, vector<int> &roots) {
        m_ = this->n;
        DSU dsu(this->n);

        for (int i = 0; i < this->n; ++i) { 
            for (int j = i + 1; j < this->n; ++j) {
                if (dsu.get_root(i) != dsu.get_root(j)) {
                    int equal = true;
                    for (int k = 0; k < this->m; ++k) {
                        if (this->outs[i][k] != this->outs[j][k]) {
                            equal = false;
                            break;
                        }
                    }

                    if (equal) {
                        dsu.merge(i, j);
                        --m_;
                    }
                }
            }
        }

        for (int i = 0; i < this->n; ++i) {
            roots[i] = dsu.get_root(i);
        }
    }

    void Split(int& m_, vector<int>& roots) {
        m_ = this->n;
        DSU dsu(this->n);

        for (int i = 0; i < this->n; ++i) {
            for (int j = i + 1; j < this->n; ++j) {
                if (roots[i] == roots[j] && dsu.get_root(i) != dsu.get_root(j)) {
                    int equal = true;

                    for (int k = 0; k < this->m; ++k) {
                        if (roots[this->moves[i][k]] != roots[this->moves[j][k]]) {
                            equal = false;
                            break;
                        }
                    }

                    if (equal) {
                        dsu.merge(i, j);
                        --m_;
                    }
                }
            }
        }

        for (int i = 0; i < this->n; ++i) {
            roots[i] = dsu.get_root(i);
        }
    }

    void generate(vector<int> &a, vector<int> &b,
        vector<int> &roots) {
        a.resize(this->n);
        b.resize(this->n);

        int counter = 0;

        for (int i = 0; i < this->n; ++i) {
            if (roots[i] == i) {
                a[counter] = i;
                b[i] = counter;
                counter++;
            }
        }
    }

    void MinimizeAufenkampHohn() {
        vector<int> roots(this->n, 0);
        int m_, m__;
        Split1(m_, roots);

        for (; 0 == 0;) {
            Split(m__, roots);
            if (m_ == m__) {
                break;
            }
            m_ = m__;
        }

        vector<int> a, b;
        generate(a, b, roots);
        Automat minim(m_, this->m, b[roots[this->q0]]);

        for (int i = 0; i < minim.n; ++i) {
            for (int j = 0; j < minim.m; ++j) {
                minim.moves[i][j] = b[roots[this->moves[a[i]][j]]];
                minim.outs[i][j] = this->outs[a[i]][j];
            }
        }

        *this = minim;
    }
};


signed main() {
    Automat a;
    a.MinimizeAufenkampHohn();
    a.Canonize();
    a.VisMealy();

	return 0;
}