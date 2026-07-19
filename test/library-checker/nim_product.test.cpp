#define PROBLEM "https://judge.yosupo.jp/problem/nim_product_64"

#define _GLIBCXX_DEBUG

#include <bits/stdc++.h>
using namespace std;
template <class T> using V = vector<T>;
using ll = long long;
#define REP(i,n) for(ll i=0; i<ll(n); i++)

#include "src/number-theory/nimber_product.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int T; cin >> T;
    NimberManager nim;

    for(int ti=0; ti<T; ti++){
        unsigned long long a,b; cin >> a >> b;
        auto ans = nim.mul(a, b);
        cout << ans << "\n";
    }

    return 0;
}
