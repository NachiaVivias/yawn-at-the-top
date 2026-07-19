#define PROBLEM "https://judge.yosupo.jp/problem/eulerian_trail_directed"

#define _GLIBCXX_DEBUG

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = 1ll << 60;
#define REP(i, n) for (ll i = 0; i < ll(n); i++)
template <class T>
using V = vector<T>;

#include "src/graph/eulerian_trail.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    
    int T; cin >> T;
    while(T--){
        int n, m; cin >> n >> m;
        
        vector<pair<int,int>> edges(m);
        for(auto& [u,v] : edges) cin >> u >> v;

        auto res = eulerian_trail(n, edges, 1);
        
        if(res.first == vector<int>(1,-1)){
            cout << "No\n";
        } else {
            cout << "Yes\n";
            for(int i=0; i<=m; i++) cout << res.first[i] << " \n"[i==m];
            for(int i=0; i<m; i++) cout << res.second[i] << " \n"[i==m-1];
        }
    }

    return 0;
}
