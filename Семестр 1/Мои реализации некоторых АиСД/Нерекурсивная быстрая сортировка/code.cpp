#pragma GCC optimize("unroll-loops", "O3")
 
#include <iostream>
#include <stack>
#include <vector>
 
using namespace std;
 
int partition(vector<int> &a, int l, int r) {
    int v = a[(l + r) / 2];
    int i = l, j = r;
    while (i <= j) {
        while (a[i] < v) {
            i++;
        }
        while (a[j] > v) {
            j--;
        }
        if (i >= j)
            break;
        swap(a[i++], a[j--]);
    }
    return j;
}
 
void quick(vector<int> &a, int l, int r) {
    stack<pair<int, int>> s;
    s.push({l, r});
    while (!s.empty()) {
        pair<int, int> b = s.top();
        s.pop();
        int l = b.first, r = b.second;
 
        if (r <= l) {
            continue;
        }
 
        int i = partition(a, l, r);
        if (i - l > r - i) {
            s.push({ l, i });
            s.push({ i + 1, r });
        }
        else {
            s.push({ i + 1, r });
            s.push({ l, i });
        }
    }
 
    if (l < r) {
        int q = partition(a, l, r);
        quick(a, l, q);
        quick(a, q + 1, r);
    }
}
 
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
 
    int n;
    vector<int> a;
    cin >> n;
    a.resize(n);
 
    for (auto& i : a) {
        cin >> i;
    }
 
    quick(a, 0, n-1);
 
    for (auto i : a) {
        cout << i << " "; 
    }
 
    return 0;
}
