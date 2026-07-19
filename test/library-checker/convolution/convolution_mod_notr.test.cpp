#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"

#define _GLIBCXX_DEBUG


#include <bits/stdc++.h>
using namespace std;
using ll = long long;
template<class T> using V = vector<T>;
#define REP(i, n) for (ll i = 0; i < ll(n); i++)

#include "src/number-theory/modint.hpp"
#include "src/fps/nft_notr.hpp"
using Mint = ModInt<998244353>;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    
    int n, m; cin >> n >> m;
    vector<Mint> a(n), b(m);
    for (int i = 0; i < n; i++) cin >> a[i].v;
    for (int i = 0; i < m; i++) cin >> b[i].v;
    auto c = multiply(a, b);
    for (int i = 0; i < n + m - 1; i++) cout << c[i] << (i == n + m - 2 ? '\n' : ' ');
}
