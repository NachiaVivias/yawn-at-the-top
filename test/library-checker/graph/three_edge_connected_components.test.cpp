#define PROBLEM "https://judge.yosupo.jp/problem/three_edge_connected_components"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;
#define REP(i,n) for(ll i=0; i<ll(n); i++)
template <class T> using V = vector<T>;

#include "src/graph/3_edge_connectivity.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int N, M; cin >> N >> M;
    vector<pair<int,int>> G(M);
    for(auto& [u,v] : G) cin >> u >> v;
    auto tcc = ThreeEdgeConnectivity(N, move(G));

    vector<vector<int>> res(tcc.num3);
    for(int i=0; i<N; i++) res[tcc.col3[i]].push_back(i);

    cout << res.size() << "\n";
    for(auto& a : res){
        cout << a.size();
        for(auto v : a) cout << " " << v;
        cout << "\n";
    }
}
