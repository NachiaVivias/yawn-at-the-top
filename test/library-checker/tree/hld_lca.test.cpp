#define PROBLEM "https://judge.yosupo.jp/problem/lca"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = 1ll << 60;
#define REP(i, n) for (ll i=0; i<ll(n); i++)
template <class T> using V = vector<T>;

#include "src/tree/hld.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    
    int N; cin >> N;
    int Q; cin >> Q;
    vector<vector<int>> t(N);
    for(int i=1; i<N; i++){
        int p; cin >> p;
        t[p].push_back(i);
        t[i].push_back(p);
    }

    auto hld = HLD(N, t, 0);
    for(int i=0; i<Q; i++){
        int u,v; cin >> u >> v;
        cout << hld.lca(u,v) << "\n";
    }

    return 0;
}
