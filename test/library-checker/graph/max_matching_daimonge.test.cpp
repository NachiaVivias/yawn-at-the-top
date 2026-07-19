#define PROBLEM "https://judge.yosupo.jp/problem/general_matching"

#define _GLIBCXX_DEBUG

#include <bits/stdc++.h>
using namespace std;
template <class T> using V = vector<T>;
using ll = long long;
#define REP(i,n) for(ll i=0; i<ll(n); i++)

#include "src/graph/max_matching-daimonge.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);

    struct E { int to; };
    
    int n, m; cin >> n >> m;
    vector<pair<ll, ll>> g;
    for(int i=0; i<m; i++){
        int u, v; cin >> u >> v;
        g.push_back({u,v});
    }
    auto res = MaxMatching(n, g);

    cout << res.size() << "\n";
    for(auto [a,b] : res) cout << a << " " << b << "\n";

    return 0;
}
