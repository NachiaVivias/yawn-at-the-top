#define PROBLEM "https://judge.yosupo.jp/problem/persistent_range_affine_range_sum"

#define _GLIBCXX_DEBUG

// !!! WARNING !!!
//   Memory Limit Exceeded is intended

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = 1ll << 60;
#define REP(i, n) for(ll i=0; i <ll(n); i++)
template <class T> using V = vector<T>;
template <class A, class B>
bool chmax(A &a, B b) { return a < b && (a=b, true); }
template <class A, class B>
bool chmin(A &a, B b) { return b < a && (a=b, true); }

#include "src/structure/persistent_avl_acl_format.hpp"

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


int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int N, Q; cin >> N >> Q;
    struct Val { Mint x; int sz; };
    struct Affine { Mint a, b; };
    struct Sz { int p; bool operator()(Val x) const { return x.sz <= p; } };
    using Ds = Node<48000000, Val,
      [](Val l, Val r){ return Val{ l.x + r.x, l.sz + r.sz }; },
      [](){ return Val{ 0, 0 }; },
      Affine,
      [](Affine f, Val x){ return Val{ f.a * x.x + f.b * x.sz, x.sz }; },
      [](Affine f, Affine x){ return Affine{ f.a * x.a, f.b + f.a * x.b }; },
      [](){ return Affine{ 1, 0 }; }
      >;
    vector<Val> init(N);
    for(int i=0; i<N; i++){
      int a; cin >> a;
      init[i] = { a, 1 };
    }
    vector<Ds*> buf;
    buf.push_back(Ds::build(init));

    auto splitlr = [&](Ds* p, int l, int r) -> tuple<Ds*, Ds*, Ds*> {
      auto [pl, pr] = p->split(Sz{r});
      auto [pll, plr] = pl->split(Sz{l});
      return { pll, plr, pr };
    };

    for(int qi=0; qi<Q; qi++){
      int t; cin >> t;
      if(t == 0){
        int k, l, r, b, c; cin >> k >> l >> r >> b >> c;
        auto [x,y,z] = splitlr(buf[k+1], l, r);
        y = y->apply(Affine{ b, c });
        buf.push_back(Ds::merge(Ds::merge(x, y), z));
      } else if(t == 1){
        int k, s, l, r; cin >> k >> s >> l >> r;
        auto [xk,yk,zk] = splitlr(buf[k+1], l, r);
        auto [xs,ys,zs] = splitlr(buf[s+1], l, r);
        buf.push_back(Ds::merge(Ds::merge(xk, ys), zk));
      } else if(t == 2){
        int k, l, r; cin >> k >> l >> r;
        auto [x,y,z] = splitlr(buf[k+1], l, r);
        cout << y->sum.x.v << "\n";
        buf.push_back(buf[k+1]);
      }
    }
    return 0;
}
