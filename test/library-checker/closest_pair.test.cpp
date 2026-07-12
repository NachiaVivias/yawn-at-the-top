#define PROBLEM "https://judge.yosupo.jp/problem/closest_pair"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define REP(i, n) for (ll i=0; i<ll(n); i++)

#include "src/geometry/primitive.hpp"
#include "src/geometry/closest_pair.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<P> ps(n);
        for(P& p : ps) cin >> p.x >> p.y;
        auto [d, i, j] = closest_pair(ps);
        cout << i << ' ' << j << '\n';
    }
}
