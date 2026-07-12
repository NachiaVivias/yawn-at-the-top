#define PROBLEM "https://judge.yosupo.jp/problem/min_of_mod_of_linear"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define REP(i, n) for(ll i=0; i <ll(n); i++)
template <class T> using V = vector<T>;

#include "src/number-theory/min_of_mod_of_linear.hpp"

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int T; cin >> T;
    while(T--){
        long long n, m, a, b; cin >> n >> m >> a >> b;
        auto res = MinModLinear(m, a, b);
        long long ansx = -1;
        for(auto [lx,rx,period,len] : res){
            if(n <= lx) break;
            if(rx < n) ansx = rx;
            else ansx = (n - 1 - lx) / period * period + lx;
        }
        long long ans = (ansx * a + b) % m;
        cout << ans << "\n";
    }
    return 0;
}
