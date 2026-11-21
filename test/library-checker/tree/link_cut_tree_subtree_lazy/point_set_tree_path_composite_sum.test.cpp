/// BEGIN https://github.com/NachiaVivias/yawn-at-the-top/blob/main/test/library-checker/tree/link_cut_tree_subtree_lazy/point_set_tree_path_composite_sum.test.cpp
#define PROBLEM "https://judge.yosupo.jp/problem/point_set_tree_path_composite_sum"



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

    struct Cluster {
        Mint stop;
        Mint amp;
        Mint capacity;
        Mint size;
        static Cluster e(){
            return { 0, 1, 0, 0 };
        }
        Cluster operator*(Cluster r) const {
            Cluster res;
            res.stop = stop + r.stop * amp + r.size * capacity;
            res.amp = amp * r.amp;
            res.capacity = capacity + r.capacity * amp;
            res.size = size + r.size;
            return res;
        }
    };

    struct F {
        void apply(F f){}
        F operator-() const { return {}; }
    };

    F id(){ return {}; }
    
    struct S{
        Cluster a;
        Cluster ra;
        void apply(F f){}
        S& operator+=(S r){
            a.stop  += a.amp * r.a.stop + ra.capacity * r.a.size;
            a.size  += r.a.size;
            ra.stop += r.a.stop;
            ra.size += r.a.size;
            return *this;
        }
        S& operator-=(S r){
            a.stop  -= a.amp * r.a.stop + ra.capacity * r.a.size;
            a.size  -= r.a.size;
            ra.stop -= r.a.stop;
            ra.size -= r.a.size;
            return *this;
        }
        void rev(){ swap(a, ra); }
    };
    
    S op(S l, S r){ return { l.a * r.a, r.ra * l.ra }; }

    S e(){ return { Cluster::e(), Cluster::e() }; }

    using Node = LCNode<S, F, e, id>;

}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    
    int N; cin >> N;
    int Q; cin >> Q;
    std::vector<Task::Node> node(N*2-1);

    auto get_v = [&](Mint x) -> Task::S {
        Task::Cluster q;
        q.size = 1;
        q.stop = x;
        q.amp = 1;
        q.capacity = 0;
        return { q, q };
    };

    auto get_e = [&](Mint b, Mint c) -> Task::S {
        Task::Cluster q;
        q.size = 0;
        q.stop = 0;
        q.amp = b;
        q.capacity = c;
        return { q, q };
    };

    for(int i=0; i<N; i++){
        int v; cin >> v;
        node[i].a = get_v(v);
        node[i].agg();
    }
    
    for(int i=0; i<N-1; i++){
        int u, v, b, c; cin >> u >> v >> b >> c;
        node[N+i].a = get_e(b, c);
        node[N+i].agg();
        node[N+i].link(&node[u]);
        node[N+i].link(&node[v]);
    }

    for(int i=0; i<Q; i++){
        int t; cin >> t;
        int r;
        if(t == 0){
            int w, x; cin >> w >> x >> r;
            node[w].expose();
            node[w].a = get_v(x);
            node[w].agg();
        }
        else if(t == 1){
            int e, c, d; cin >> e >> c >> d >> r;
            node[N+e].expose();
            node[N+e].a = get_e(c, d);
            node[N+e].agg();
        }
        node[r].evert();
        cout << node[r].path.a.stop.v << "\n";
    }

    return 0;
}
/// END https://github.com/NachiaVivias/yawn-at-the-top/blob/main/test/library-checker/tree/link_cut_tree_subtree_lazy/point_set_tree_path_composite_sum.test.cpp
