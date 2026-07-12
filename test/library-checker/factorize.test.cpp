#define PROBLEM "https://judge.yosupo.jp/problem/factorize"

#include "src/common/template.hpp"

template<class T>
T pow_mod(T a, T n, T m){
    if(!n) return 1 % m;
    T r = pow_mod(a*a%m, n/2, m);
    if(n%2) r = r * a % m;
    return r;
}

#include "src/number-theory/miller_rabin.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    
    int t; cin >> t;
    while(t--) {
        long long n; cin >> n;
        auto res = pollard(n);
        sort(res.begin(), res.end());
        cout << res.size();
        for(auto a : res) cout << " " << a;
        cout << "\n";
    }

    return 0;
}
