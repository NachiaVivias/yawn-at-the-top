#define PROBLEM "https://yukicoder.me/problems/no/186"

#include <bits/stdc++.h>
using namespace std;
template <class T> using V = vector<T>;
using ll = long long;
#define REP(i,n) for(ll i=0; i<ll(n); i++)

#include "src/number-theory/crt.hpp"

int main() {
    vector<long long> x(3), y(3);
    for(int i = 0; i < 3; i++) {
        cin >> x[i] >> y[i];
    }
    auto [ans, l] = crt(x, y);
    if(l == -1) cout << "-1\n";
    else if(ans == 0) cout << l << endl;
    else cout << ans << endl;
}
