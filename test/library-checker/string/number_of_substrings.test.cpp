#define PROBLEM "https://judge.yosupo.jp/problem/number_of_substrings"

#define _GLIBCXX_DEBUG

#include <bits/stdc++.h>
using namespace std;
template <class T> using V = vector<T>;
using ll = long long;
#define REP(i,n) for(ll i=0; i<ll(n); i++)

#include "src/string/suffix_array.hpp"
#include "src/string/lcp_array.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    
    string s; cin >> s;
    auto sa = sa_is(s, 200);
    auto lcp = lcp_array(s, sa);
    long long n = s.size();
    long long ans = n * (n + 1) / 2;
    for(int i=0; i<n; i++) ans -= lcp[i];
    cout << ans << '\n';

    return 0;
}
