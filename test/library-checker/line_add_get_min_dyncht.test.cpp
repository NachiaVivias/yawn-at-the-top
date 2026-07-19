#define PROBLEM "https://judge.yosupo.jp/problem/line_add_get_min"

// maybe slows down std::multiset
// #define _GLIBCXX_DEBUG

#include <bits/stdc++.h>
using namespace std;
template <class T> using V = vector<T>;
using ll = long long;
#define REP(i,n) for(ll i=0; i<ll(n); i++)

#include "src/convex/dynamic_convex_hull.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    
    ll N, Q; cin >> N >> Q;

    LineContainer ds;
    for(ll i=0; i<N; i++){
        ll a, b; cin >> a >> b;
        ds.add(-a, -b);
    }

    for(ll i=0; i<Q; i++){
        ll t; cin >> t;
        if(t == 0){
            ll a, b; cin >> a >> b;
            ds.add(-a, -b);
        } else {
            ll p; cin >> p;
            cout << -ds.query(p) << "\n";
        }
    }
    
    return 0;
}
