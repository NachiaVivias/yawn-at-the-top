#define PROBLEM "https://judge.yosupo.jp/problem/sum_of_floor_of_linear"

#define _GLIBCXX_DEBUG

#include <bits/stdc++.h>
using namespace std;
template <class T> using V = vector<T>;
using ll = long long;
#define REP(i,n) for(ll i=0; i<ll(n); i++)

#include "src/number-theory/floor_sum_monoid.hpp"

struct S { ll x, y, sum; };
S op(const S& l, const S& r){
  return {
    l.x + r.x,
    l.y + r.y,
    l.sum + r.sum + l.y * r.x
  };
}
S e = { 0,0,0 };

int main() {
  cin.tie(0)->sync_with_stdio(0);

  long long T; cin >> T;
  while(T--){
    long long n,m,a,b; cin >> n >> m >> a >> b;
    auto ans = FloorSumMonoid<ll, S, op>(n, m, a, b, {1,0,0}, {0,1,0}, {0,0,0}).sum;
    cout << ans << "\n";
  }

  return 0;
}
