/// BEGIN https://github.com/NachiaVivias/yawn-at-the-top/blob/main/test/library-checker/tree/dynamic_tree_subtree_add_subtree_sum.test.cpp
#define PROBLEM "https://judge.yosupo.jp/problem/dynamic_tree_subtree_add_subtree_sum"



#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = 1ll << 60;
#define REP(i, n) for (ll i=0; i<ll(n); i++)
template <class T> using V = vector<T>;

#include "src/tree/link_cut_tree_subtree_lazy.hpp"

using ull = unsigned long long;
using F = ull;
struct S{
    ull c, x;
    void apply(F f){ x += f * c; }
    S& operator+=(S r){ return *this = { c + r.c, x + r.x }; }
    S& operator-=(S r){ return *this = { c - r.c, x - r.x }; }
};
S op(S l, S r){ return l += r; }
S e(){ return {0, 0}; }
F id(){ return 0; }

using LC = LCNode<S, F, e, id>;

void testcase(){
    ll N, Q; cin >> N >> Q;
    V<ll> A(N); REP(i,N) cin >> A[i];
    V<LC> P(N);
    REP(i,N){ P[i].a = {1, A[i]}; P[i].agg(); }
    REP(i,N-1){ ll u,v; cin >> u >> v; P[u].link(&P[v]); }

    REP(qi,Q){
        ll ty; cin >> ty;
        if(ty == 0){
            ll u,v,w,x; cin >> u >> v >> w >> x;
            P[u].evert();
            P[v].cut();
            P[w].link(&P[x]);
        } else if(ty == 1){
            ll v,p,x; cin >> v >> p >> x;
            P[p].evert();
            P[v].cut();
            P[v].apply(x);
            P[v].link(&P[p]);
        } else {
            ll v,p; cin >> v >> p;
            P[p].evert();
            P[v].cut();
            cout << P[v].sum.x << "\n";
            P[v].link(&P[p]);
        }
    }
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    testcase();
    return 0;
}
/// END https://github.com/NachiaVivias/yawn-at-the-top/blob/main/test/library-checker/tree/dynamic_tree_subtree_add_subtree_sum.test.cpp
