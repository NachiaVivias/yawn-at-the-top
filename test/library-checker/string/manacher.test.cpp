#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_palindromes"

#include <bits/stdc++.h>
using namespace std;
template <class T> using V = vector<T>;
using ll = long long;
#define REP(i,n) for(ll i=0; i<ll(n); i++)

#include "src/string/manacher.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    
    string s; cin >> s;
    auto x = manacher(s, '$');
    int n = x.size();
    for(int i=1; i<n-1; i++){
        if(i != 1) cout << " ";
        cout << x[i];
    } cout << "\n";

    return 0;
}
