#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_set>

using namespace std;

struct Vertex {
    std::string out;
    int in, cnt;

    bool operator==(const Vertex& other) const {
        return ((this->out == other.out)
            && (this->in == other.in));
    }
};

struct VertexHasher {
    size_t operator()(const Vertex& v) const {
        std::size_t hash = 0;
        std::hash<std::string> str_hasher;
        hash ^= str_hasher(v.out) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        std::hash<int> int_hasher;
        hash ^= int_hasher(v.in) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        return hash;
    }
};

bool cmp(Vertex a, Vertex b) {
    return ((a.in < b.in) || ((a.in == b.in) && (a.out < b.out)));
}

struct MooreAutomat;

struct MileAutomat {
    int n, m, q0;
    vector<vector<int>> moves;
    vector<vector<int>> outs;
    vector<string> in, out;

    MileAutomat();
    void Input();
    MooreAutomat toMoore();
};

struct MooreAutomat {
    vector<Vertex> vertxs;
    vector<string> in, out;
    pair<Vertex, int> find(Vertex a);
    unordered_set<Vertex, VertexHasher> to_optimize;
    void VisMoore(MileAutomat mile);
};


pair<Vertex, int> MooreAutomat::find(Vertex a) {
    int i = 0;
    auto it = this->to_optimize.find(a);
    if (it != this->to_optimize.end()) {
        return { *it, true };
    }

    return { a, false };
}

void MooreAutomat::VisMoore(MileAutomat mile) {
    cout << "digraph {\n\trankdir = LR\n";

    for (auto vert : this->vertxs) {
        cout << "\t" << vert.cnt << " [label = \"(" << vert.out;
        cout << ")\"]\n";

        for (int j = 0; j < mile.m; ++j) {
            Vertex a = { to_string(mile.moves[vert.in][j]) + "," + mile.out[mile.outs[vert.in][j]], mile.moves[vert.in][j], 0 };
            pair<Vertex, int> x = this->find(a);
            cout << "\t" << vert.cnt << " -> " << x.first.cnt;
            cout << " [label = \"" << mile.in[j] << "\"]\n";
        }
    }

    cout << "}";
}


MileAutomat::MileAutomat() {
    Input();
}

void MileAutomat::Input() {
    cin >> this->m;
    this->in.resize(this->m);
    for (int i = 0; i < this->m; ++i) {
        cin >> in[i];
    }


    cin >> this->q0;
    out.resize(q0);
    for (int i = 0; i < q0; ++i) {
        cin >> out[i];
    }

    cin >> n;
    moves.resize(n, vector<int>(m));
    for (auto& i : moves) {
        for (auto& j : i) {
            cin >> j;
        }
    }

    outs.resize(n, vector<int>(m));
    for (auto& i : outs) {
        for (auto& j : i) {
            cin >> j;
        }
    }
}

MooreAutomat MileAutomat::toMoore() {
    MooreAutomat moore;

    int count = 0;
    for (int i = 0; i < this->outs.size(); ++i) {
        for (int j = 0; j < this->outs[i].size(); ++j) {
            Vertex a = { to_string(this->moves[i][j]) + ","
                         + this->out[this->outs[i][j]],
                         this->moves[i][j], count };

            // заменить на хэш таблицу
            pair<Vertex, int> ex = moore.find(a);
            if (!ex.second) {
                moore.vertxs.push_back(a);
                moore.to_optimize.insert(a);
                ++count;
            }

        }
    }

    sort(moore.vertxs.begin(), moore.vertxs.end(), cmp);

    return moore;
}


signed main() {
    MileAutomat a;
    MooreAutomat b = a.toMoore();
    b.VisMoore(a);

    return 0;
}