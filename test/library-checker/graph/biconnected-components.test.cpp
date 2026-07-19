#define PROBLEM "https://judge.yosupo.jp/problem/biconnected_components"

#define _GLIBCXX_DEBUG

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = 1ll << 60;
#define REP(i, n) for (ll i=0; i<ll(n); i++)
template <class T> using V = vector<T>;

#include "src/graph/biconnectivity.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    
    int N, M; cin >> N >> M;
    vector<vector<int>> G(N);
    for(int i=0; i<M; i++){
        int u, v; cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    auto bi = Biconnectivity(N, G);
    vector<vector<int>> H(bi.num_bcc);
    for(auto [u,v] : bi.bct) H[u].push_back(v);
    cout << bi.num_bcc << "\n";
    for(auto& h : H){
        cout << h.size();
        for(auto a : h) cout << " " << a;
        cout << "\n";
    }
}
