#define PROBLEM "https://judge.yosupo.jp/problem/scc"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
template <class T>
using V = vector<T>;
#define REP(i, n) for (ll i=0; i<ll(n); i++)
template<class A, class B>
bool chmax(A &a, B b) { return a < b && (a = b, true); }
template<class A, class B>
bool chmin(A &a, B b) { return b < a && (a = b, true); }
#include "src/graph/scc.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    
    int n, m; cin >> n >> m;
    vector<vector<int>> g(n);
    for(int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        g[a].push_back(b);
    }
    auto [nscc, sccid] = scc(n, g);
    vector<vector<int>> groups(nscc);
    for(int i = 0; i < n; i++) groups[sccid[i]].push_back(i);
    cout << nscc << '\n';
    for(const auto& gr : groups) {
        cout << gr.size();
        for(int i : gr) cout << ' ' << i;
        cout << '\n';
    }
}
