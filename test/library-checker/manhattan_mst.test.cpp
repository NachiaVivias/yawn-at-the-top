#define PROBLEM "https://judge.yosupo.jp/problem/manhattanmst"

#include <bits/stdc++.h>
using namespace std;
template <class T> using V = vector<T>;
using ll = long long;
#define REP(i,n) for(ll i=0; i<ll(n); i++)

#include "src/graph/manhattan_mst.hpp"

struct DsuFast{
private:
    std::vector<int> w;
public:
    DsuFast(int n = 0) : w(n, -1) {}
    int leader(int u){
        if(w[u] < 0) return u;
        return w[u] = leader(w[u]);
    }
    int operator[](int u){ return leader(u); }
    int merge(int u, int v){
        u = leader(u);
        v = leader(v);
        if(u == v) return u;
        if(-w[u] < -w[v]) std::swap(u, v);
        w[u] += w[v];
        w[v] = u;
        return u;
    }
    int size(int u){ return -w[leader(u)]; }
    bool same(int u, int v){ return leader(u) == leader(v); }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    vector<int> x(n), y(n);
    for(int i=0; i<n; i++) cin >> x[i] >> y[i];

    auto es = manhattan_mst(x, y);
    sort(es.begin(), es.end());
    
    auto dsu = DsuFast(n);
    long long cost = 0;
    vector<pair<int,int>> ans;
    for(auto [c,u,v] : es){
        if(dsu.same(u,v)) continue;
        dsu.merge(u,v);
        cost += c;
        ans.push_back({u,v});
    }

    cout << cost << "\n";
    for(auto [u,v] : ans) cout << u << " " << v << "\n";

    return 0;
}
