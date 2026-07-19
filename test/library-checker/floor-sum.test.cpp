#define PROBLEM "https://judge.yosupo.jp/problem/sum_of_floor_of_linear"

#define _GLIBCXX_DEBUG

#include <bits/stdc++.h>
using namespace std;
template <class T> using V = vector<T>;
using ll = long long;
#define REP(i,n) for(ll i=0; i<ll(n); i++)

#include "src/number-theory/floor-sum.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    
    int T; cin >> T;
    
    for(int t=0; t<T; t++){
        long long n, m, a, b; cin >> n >> m >> a >> b;
        auto ans = gauss_sum(n, a, b, m);
        cout << ans << "\n";
    }

    return 0;
}
