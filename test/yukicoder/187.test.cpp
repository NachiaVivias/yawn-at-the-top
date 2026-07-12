#define PROBLEM "https://yukicoder.me/problems/no/187"

#include <bits/stdc++.h>
using namespace std;
template <class T> using V = vector<T>;
using ll = long long;
#define REP(i,n) for(ll i=0; i<ll(n); i++)

#include "src/number-theory/crt.hpp"
#include "src/number-theory/garner.hpp"

const long long MOD = 1000000007;
struct Mi { long long x; Mi(long long y = 0) : x((y % MOD + MOD) % MOD) {} };
Mi operator+(Mi l, Mi r){ return l.x + r.x; }
Mi operator*(Mi l, Mi r){ return l.x * r.x; }

int main() {
    int n; cin >> n;
    vector<long long> b(n), m(n);
    bool zero = true;
    for(int i = 0; i < n; i++) {
        cin >> b[i] >> m[i];
        for(int j = 0; j < i; j++) {
            if(!coprimize_mod_system(b[j], m[j], b[i], m[i])) {
                cout << "-1\n";
                return 0;
            }
        }
        zero &= b[i] == 0;
    }
    Mi ans = garner<Mi>(m)(b);
    if(zero){
        ans = 1;
        for(long long mm : m) ans = ans * mm;
    }
    cout << ans.x << "\n";

    return 0;
}
