#define PROBLEM "https://judge.yosupo.jp/problem/tree_path_composite_sum"

// maybe slows down std::lower_bound
// #define _GLIBCXX_DEBUG

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
  vector<vector<int>> E(N);
  vector<Mint> A(N), B(N-1), C(N-1);
  vector<pair<pair<int,int>, int>> dict;
  for(int i=0; i<N; i++){
    int a; cin >> a; A[i] = a;
  }
  for(int i=0; i<N-1; i++){
    int u,v,b,c; cin >> u >> v >> b >> c;
    if(u > v) swap(u, v);
    E[u].push_back(v);
    E[v].push_back(u);
    B[i] = b;
    C[i] = c;
    dict.push_back({ {u,v}, i });
  }
  sort(dict.begin(), dict.end());
  struct S { Mint x, z; int root; };
  vector<S> rootval(N);
  for(int i=0; i<N; i++) rootval[i] = { A[i], 1, i };
  TreeDP dp(E, rootval,
    [&](S l, S r) -> S { return { l.x + r.x, l.z + r.z, l.root }; },
    [&](S a, int v, int w) -> S {
        int e = lower_bound(dict.begin(), dict.end(), make_pair(make_pair(min(v,w), max(v,w)),-1))->second;
        return { a.x * B[e] + a.z * C[e], a.z, w }; },
    0, {0,0,-1});
  for(int i=0; i<N; i++){
    if(i) cout << " ";
    cout << dp.get(i).x.v;
  } cout << "\n";
}

int main(){
  cin.tie(0)->sync_with_stdio(0);
  testcase();
  return 0;
}
