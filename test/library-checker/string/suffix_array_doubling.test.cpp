#define PROBLEM "https://judge.yosupo.jp/problem/suffixarray"

#include <bits/stdc++.h>
using namespace std;
template <class T> using V = vector<T>;
using ll = long long;
#define REP(i,n) for(ll i=0; i<ll(n); i++)

#include "src/string/suffix_array_doubling.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    
    string s; cin >> s;
    auto ans = suffix_array(s);
    for(int i=0; i<int(s.size()); i++){
        if(i) cout << " ";
        cout << ans[i];
    } cout << "\n";

    return 0;
}
