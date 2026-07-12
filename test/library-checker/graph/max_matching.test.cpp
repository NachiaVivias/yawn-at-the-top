#define PROBLEM "https://judge.yosupo.jp/problem/general_matching"

#include <bits/stdc++.h>
using namespace std;
template <class T> using V = vector<T>;
using ll = long long;
#define REP(i,n) for(ll i=0; i<ll(n); i++)

#include "src/graph/max_matching.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);

    struct E { int to; };
    
    int n, m; cin >> n >> m;
    vector<vector<E>> g(n);
    for(int i=0; i<m; i++){
        int u, v; cin >> u >> v;
        g[u].push_back({v});
        g[v].push_back({u});
    }
    auto res = MaxMatching(g);
    vector<pair<int,int>> ans;
    for(int i=0; i<n; i++) if(i < res.mt[i]){
        ans.push_back({ i, res.mt[i] });
    }

    cout << ans.size() << "\n";
    for(auto [a,b] : ans) cout << a << " " << b << "\n";

    return 0;
}
