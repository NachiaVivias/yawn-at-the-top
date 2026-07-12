#define PROBLEM "https://judge.yosupo.jp/problem/dynamic_tree_vertex_add_path_sum"



#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = 1ll << 60;
#define REP(i, n) for (ll i=0; i<ll(n); i++)
template <class T> using V = vector<T>;

#include "src/tree/link_cut_tree.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    
    int N; cin >> N;
    int Q; cin >> Q;
    std::vector<LCNode> node(N);
    for(int i=0; i<N; i++){
        cin >> node[i].a.x;
        node[i].agg();
    }
    
    for(int i=0; i<N-1; i++){
        int u,v; cin >> u >> v;
        node[u].link(&node[v]);
    }

    for(int i=0; i<Q; i++){
        int t; cin >> t;
        if(t == 0){
            int u,v,w,x; cin >> u >> v >> w >> x;
            node[u].evert();
            node[v].cut();
            node[w].link(&node[x]);
        }
        else if(t == 1){
            int p, x; cin >> p >> x;
            node[p].expose();
            node[p].a.x += x;
            node[p].agg();
        }
        else {
            int u,v; cin >> u >> v;
            node[u].evert();
            node[v].expose();
            cout << node[v].sum.x << "\n";
        }
    }

    return 0;
}
