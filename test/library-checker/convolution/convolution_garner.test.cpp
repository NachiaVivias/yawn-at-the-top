#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod_1000000007"

#define _GLIBCXX_DEBUG


#include <bits/stdc++.h>
using namespace std;
using ll = long long;
template <class T> using V = vector<T>;
#define REP(i, n) for (ll i = 0; i < ll(n); i++)

#include "src/number-theory/modint.hpp"
#include "src/number-theory/crt.hpp"
#include "src/number-theory/garner.hpp"
#include "src/fps/nft.hpp"
#include "src/fps/garner_convolution.hpp"


int main() {
    cin.tie(0)->sync_with_stdio(0);
    
    int n, m; cin >> n >> m;
    using MI = ModInt<1000000007>;
    vector<MI> a(n), b(m);
    for(int i = 0; i < n; i++) cin >> a[i].v;
    for(int i = 0; i < m; i++) cin >> b[i].v;
    auto c = multiply_garner(a, b);
    for(int i = 0; i < n+m-1; i++) cout << c[i] << (i == n+m-2 ? '\n' : ' ');
}
