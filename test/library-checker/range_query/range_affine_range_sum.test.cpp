#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_range_sum"

#define _GLIBCXX_DEBUG

#include <bits/stdc++.h>
using namespace std;
template <typename T>
using V = vector<T>;
#include "src/structure/lazysegtree.hpp"

using ll = long long;
constexpr ll MOD = 998244353;

struct S {
    long long val, sz;
};
S op(S l, S r) {
    return S((l.val+r.val)%MOD, l.sz+r.sz);
}
struct F {
    long long a, b;
};
S mapping(F f, S x) {
    return S((f.a*x.val+f.b*x.sz)%MOD, x.sz);
}
F composition(F f, F g) {
    return F(f.a*g.a%MOD, (f.a*g.b+f.b)%MOD);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    
    int n, q; cin >> n >> q;
    vector<S> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i].val;
        a[i].sz = 1;
    }
    LazySegtree<S, F, op, composition, mapping> seg(a, S(0, 0), F(1, 0));
    while(q--) {
        int op; cin >> op;
        if(op == 0) {
            long long l, r, b, c; cin >> l >> r >> b >> c;
            seg.apply(l, r, F(b, c));
        } else {
            int l, r; cin >> l >> r;
            cout << seg.prod(l, r).val << '\n';
        }
    }
}
