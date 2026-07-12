#define PROBLEM "https://yukicoder.me/problems/no/2584"

/*

No.2584 The University of Tree

頂点に接続する辺の cyclic-順序を考慮する必要がある全方位木DP

*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = 1ll << 60;
#define REP(i,n) for(ll i=0; i<ll(n); i++)
template <class T> using V = vector<T>;
template <class A, class B> void chmax(A& l, const B& r){ if(l < r) l = r; }
template <class A, class B> void chmin(A& l, const B& r){ if(r < l) l = r; }

#include "src/tree/tree_dp.hpp"

template <int MD, int g = 3>
struct ModInt {
  using M = ModInt;
  const static inline M G = g;
  unsigned int v;
  ModInt() : v(0) {}
  ModInt(ll w) : v(w % MD + MD) {
    if(v >= MD) v -= MD;
  }
  static M raw(unsigned int v) {
    M res;
    res.v = (v < MD) ? v : v - MD;
    return res;
  }
  explicit operator bool() const {
    return v != 0;
  }
  M operator-() const {
    return M() - *this;
  }
  M operator+(M r) const {
    return raw(v + r.v);
  }
  M operator-(M r) const {
    return raw(v + MD - r.v);
  }
  M operator*(M r) const {
    return raw(ll(v) * r.v % MD);
  }
  M operator/(M r) const {
    return *this * r.inv();
  }
  M& operator+=(M r) {
    return *this = *this + r;
  }
  M& operator-=(M r) {
    return *this = *this - r;
  }
  M& operator*=(M r) {
    return *this = *this * r;
  }
  M& operator/=(M r) {
    return *this = *this / r;
  }
  bool operator==(M r) const {
    return v == r.v;
  }
  M pow(ll n) const {
    M x = *this, r = 1;
    while (n) {
      if (n & 1) r *= x;
      x *= x;
      n >>= 1;
    }
    return r;
  }
  M inv() const {
    return pow(MD - 2);
  }
  friend ostream& operator<<(ostream& os, M r) {
    return os << r.v;
  }
};
using Mint = ModInt<998244353, 3>;


void testcase(){
  int N; cin >> N;
  vector<vector<int>> E(N*2);
  vector<int> ex(N);
  for(int i=0; i<N; i++){
    E[i].push_back(N+i);
    E[N+i].push_back(i);
  }
  for(int i=0; i<N; i++){
    int C; cin >> C;
    for(int j=0; j<C; j++){
      int e; cin >> e; e--;
      E[i].push_back(N*2 + e);
      ex[e] ^= i;
    }
  }
  for(int i=0; i<N; i++) for(int& e : E[i]) if(e >= N*2) e = ex[e - N*2] ^ i;
  struct S { Mint r, a; };
  vector<S> rootval(N*2, { 1, 0 });
  for(int i=0; i<N; i++) rootval[N+i].a = 1;
  TreeDP dp(E, rootval,
    [&](S l, S r) -> S { return { l.r * r.r, l.a + l.r * r.a }; },
    [&](S a, int v, int w) -> S { return { w+1, a.a * (v < N ? v+1 : 1) }; },
    0, {1,0});
  for(int i=0; i<N; i++) cout << (dp.get(N+i).a - 1).v << "\n";
}

int main(){
  cin.tie(0)->sync_with_stdio(0);
  testcase();
  return 0;
}
