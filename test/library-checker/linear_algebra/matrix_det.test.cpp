#define PROBLEM "https://judge.yosupo.jp/problem/matrix_det"


#include <bits/stdc++.h>
using namespace std;
template <class T> using V = vector<T>;
template <class T> using VV = V<V<T>>;
using ll = long long;
#define REP(i,n) for(ll i=0; i<ll(n); i++)

#include "src/number-theory/modint.hpp"
using Mint = ModInt<998244353>;
#include "src/other/matrix.hpp"
using Mat = Matrix<Mint>;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    
    int n; cin >> n;
    Mat mat(n, n);
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            int x; cin >> x;
            mat.set(i,j,x);
        }
    }
    
    cout << mat.getdet().v << "\n";

    return 0;
}
