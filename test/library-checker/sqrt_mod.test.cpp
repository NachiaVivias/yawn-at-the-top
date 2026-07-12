#define PROBLEM "https://judge.yosupo.jp/problem/sqrt_mod"

#include <bits/stdc++.h>
using namespace std;
template <class T> using V = vector<T>;
using ll = long long;
#define REP(i,n) for(ll i=0; i<ll(n); i++)

#include "src/number-theory/crt.hpp"
#include "src/number-theory/tonelli_shanks.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    
    int T; cin >> T;
    
    for(int t=0; t<T; t++){
        int y, p; cin >> y >> p;
        auto ans = Tonelli_Shanks(y, p);
        cout << ans << "\n";
    }

    return 0;
}
