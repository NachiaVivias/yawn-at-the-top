#define PROBLEM "https://judge.yosupo.jp/problem/suffixarray"

#define _GLIBCXX_DEBUG

#include <bits/stdc++.h>
using namespace std;
template <class T> using V = vector<T>;
using ll = long long;
#define REP(i,n) for(ll i=0; i<ll(n); i++)

#include "src/string/suffix_array.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    
    string s; cin >> s;
    V<int> sv;
    for(auto a : s) sv.push_back(a);
    auto ans = sa_is(sv, 200);
    for(int i=0; i<int(s.size()); i++){
        if(i) cout << " ";
        cout << ans[i];
    } cout << "\n";

    return 0;
}
