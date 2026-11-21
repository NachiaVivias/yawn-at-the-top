/// BEGIN https://github.com/NachiaVivias/yawn-at-the-top/blob/main/test/library-checker/tree/link_cut_tree_subtree_lazy/dynamic_tree_subtree_add_subtree_sum.test.cpp
#define PROBLEM "https://judge.yosupo.jp/problem/dynamic_tree_subtree_add_subtree_sum"



#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = 1ll << 60;
#define REP(i, n) for (ll i=0; i<ll(n); i++)
template <class T> using V = vector<T>;

#include "src/tree/link_cut_tree_subtree.hpp"

namespace Task {

    struct F {
        ll v;
        void apply(F f){ v += f.v; }
        F operator-() const { return {-v}; }
    };

    F id(){ return {}; }
    
    struct S{
        ll sum;
        ll sz;
        void apply(F f){ sum += sz * f.v; }
        S& operator+=(S r){ sum += r.sum; sz += r.sz; return *this; }
        S& operator-=(S r){ sum -= r.sum; sz -= r.sz; return *this; }
        void rev(){}
    };
    
    S op(S l, S r){ return { l.sum + r.sum, l.sz + r.sz }; }

    S e(){ return { 0, 0 }; }

    using Node = LCNode<S, F, e, id>;

}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    
    int N; cin >> N;
    int Q; cin >> Q;
    std::vector<Task::Node> node(N);
    for(int i=0; i<N; i++){
        cin >> node[i].a.sum;
        node[i].a.sz = 1;
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
            int v, p, x; cin >> v >> p >> x;
            node[p].evert();
            node[v].expose();

            auto buf = node[v].c[0];
            node[v].c[0] = 0;
            node[v].agg();
            node[v].apply({x});
            node[v].prop();
            node[v].c[0] = buf;
            node[v].agg();
        }
        else {
            int v,p; cin >> v >> p;
            node[p].evert();
            node[v].expose();

            auto buf = node[v].c[0];
            node[v].c[0] = 0;
            node[v].agg();
            cout << node[v].path.sum << "\n";
            node[v].c[0] = buf;
            node[v].agg();
        }
    }

    return 0;
}

/// END https://github.com/NachiaVivias/yawn-at-the-top/blob/main/test/library-checker/tree/link_cut_tree_subtree_lazy/dynamic_tree_subtree_add_subtree_sum.test.cpp
