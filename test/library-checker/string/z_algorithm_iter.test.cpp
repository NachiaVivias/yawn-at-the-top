#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"

#include <bits/stdc++.h>
using namespace std;
template <class T> using V = vector<T>;
using ll = long long;
#define REP(i,n) for(ll i=0; i<ll(n); i++)

#include "src/string/z_algorithm_iter.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    
    string s; cin >> s;
    auto ans = z_algorithm(s.begin(), s.end());
    for(int i=0; i<int(s.size()); i++){
        if(i) cout << " ";
        cout << ans[i];
    } cout << "\n";

    return 0;
}
