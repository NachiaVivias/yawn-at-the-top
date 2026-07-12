#define PROBLEM "https://judge.yosupo.jp/problem/discrete_logarithm_mod"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define REP(i, n) for (ll i = 0; i < ll(n); i++)

#include "src/number-theory/bsgs.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    
    int t; cin >> t;
    while(t--) {
        long long x, y, m; cin >> x >> y >> m;
        if(m == 1) {
            cout << "0\n";
            continue;
        }
        auto mod_prod = [&](long long a, long long b) { return a * b % m; };
        cout << bsgs(x, 1LL, y, mod_prod, 1LL, mod_prod, m) << '\n';
    }
}
