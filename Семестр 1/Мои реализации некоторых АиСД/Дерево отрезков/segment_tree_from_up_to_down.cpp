#pragma GCC optimize("O3", "unroll-loops")

#include <iostream>
#include <vector>

typedef long long ll;

using namespace std;

vector<ll> a;

struct SegmentTree {
	struct Vertex {
		ll value;
	};

	const ll ZERO = 0;

	Vertex func(Vertex& a, Vertex& b) {
		while (b.value) {
			a.value %= b.value;
			swap(a, b);
		}
		return { a };
	}

	Vertex combine(Vertex a, Vertex b) {
		return func(a, b);
	}

	vector<Vertex> t;

	void init() {
		t.resize(4 * a.size());
		build(0, 0, a.size());
	}

	void build(ll x, ll xl, ll xr) {
		if (xl == xr - 1) {
			t[x] = { a[xl] };
			return;
		}

		ll xm = (xl + xr) / 2;
		build(2 * x + 1, xl, xm);
		build(2 * x + 2, xm, xr);
		t[x] = combine(t[2 * x + 1], t[2 * x + 2]);
	}

	void update(ll x, ll xl, ll xr, ll ind, ll val) {
		if (xl == xr - 1) {
			t[x] = { val };
			return;
		}

		ll xm = (xl + xr) / 2;
		if (ind < xm) {
			update(2 * x + 1, xl, xm, ind, val);
		}
		else {
			update(2 * x + 2, xm, xr, ind, val);
		}

		t[x] = func(t[2 * x + 1], t[2 * x + 2]);
	}

	Vertex request(ll x, ll xl, ll xr, ll l, ll r) {
		if (xl >= r || l >= xr) {
			return { ZERO };
		}

		if (xl >= l && xr <= r) {
			return t[x];
		}

		ll xm = (xl + xr) / 2;
		return combine(request(2 * x + 1, xl, xm, l, r), request(2 * x + 2, xm, xr, l, r));
	}
};

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	ll n;
	cin >> n;

	a.resize(n);
	for (auto& i : a) {
		cin >> i;
	}

	SegmentTree sg;
	sg.init();

	ll m;
	cin >> m;
	ll l, r;
	while (m--) {
		cin >> l >> r;
		cout << sg.request(0, 0, n, l-1, r).value << " ";
	}
	
	return 0;
}
