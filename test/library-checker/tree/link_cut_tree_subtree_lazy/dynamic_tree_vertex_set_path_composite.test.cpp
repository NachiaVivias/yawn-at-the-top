#define PROBLEM "https://judge.yosupo.jp/problem/dynamic_tree_vertex_set_path_composite"



#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = 1ll << 60;
#define REP(i, n) for (ll i=0; i<ll(n); i++)
template <class T> using V = vector<T>;

#include "src/tree/link_cut_tree_subtree.hpp"

#include "src/number-theory/modint.hpp"

using Mint = ModInt<998244353>;

namespace Task {

    struct Affine {
        Mint a = 1, c = 0;
        Affine operator*(Affine r) const { return { a * r.a, c * r.a + r.c }; }
    };

    struct F {
        void apply(F f){}
        F operator-() const { return {}; }
    };

    F id(){ return {}; }
    
    struct S{
        Affine a;
        Affine ra;
        void apply(F f){}
        S& operator+=(S r){ return *this; }
        S& operator-=(S r){ return *this; }
        void rev(){ swap(a, ra); }
    };
    
    S op(S l, S r){ return { l.a * r.a, r.ra * l.ra }; }

    S e(){ return S(); }

    using Node = LCNode<S, F, e, id>;

}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    
    int N; cin >> N;
    int Q; cin >> Q;
    std::vector<Task::Node> node(N);
    for(int i=0; i<N; i++){
        int a, b; cin >> a >> b;
        node[i].a.a = node[i].a.ra = {Mint(a), Mint(b)};
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
            int p, c, d; cin >> p >> c >> d;
            node[p].expose();
            node[p].a.a = node[p].a.ra = {Mint(c), Mint(d)};
            node[p].agg();
        }
        else {
            int u,v,x; cin >> u >> v >> x;
            node[u].evert();
            node[v].expose();
            cout << (node[v].path.a.a * Mint(x) + node[v].path.a.c).v << "\n";
        }
    }

    return 0;
}
