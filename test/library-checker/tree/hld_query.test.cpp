#define PROBLEM "https://judge.yosupo.jp/problem/vertex_set_path_composite"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = 1ll << 60;
#define REP(i, n) for (ll i=0; i<ll(n); i++)
template <class T> using V = vector<T>;

#include "src/tree/hld.hpp"

template<int MD, int g = 3>
struct ModInt {
  using M = ModInt;
  const static inline M G = g;
  unsigned int v;
  ModInt(long long _v = 0){
    set_v(_v % MD + MD);
  }
  M& set_v(unsigned int _v){ v = (_v < MD) ? _v : _v - MD; return  *this; }
  explicit operator bool() const { return v != 0; }
  M operator-() const { return M() - *this; }
  M operator+(M r) const { return M().set_v(v + r.v); }
  M operator-(M r) const { return M().set_v(v + MD - r.v); }
  M operator*(M r) const { return M().set_v((long long)(v) * r.v % MD); }
  M operator/(M r) const { return * this * r.inv(); }
  M& operator+=(M r){ return *this = *this + r; }
  M& operator-=(M r){ return *this = *this - r; }
  M& operator*=(M r){ return *this = *this * r; }
  M& operator/=(M r){ return *this = *this / r; }
  bool operator==(const M& r) const { return v == r.v; }
  M pow(long long n) const {
    M x = *this, r = 1;
    while(n){
      if(n&1) r *= x;
      x *= x;
      n >>= 1;
    }
    return r;
  }
  M inv() const { return pow(MD - 2); }
  friend ostream& operator<<(ostream& os, const M& r){
    return os << r.v;
  }
};

using Mint = ModInt<998244353>;

struct S {
    Mint a;
    Mint b;
    Mint operator()(Mint x) const { return x * a + b; }
};
S op(S l, S r){ return { l.a * r.a, l.b * r.a + r.b }; }
struct Segtree {
  int N;
  vector<S> A;
  void agg(int i){ A[i] = op(A[i*2], A[i*2+1]); }
  Segtree(int n, S e) : N(1){
    while(N < n) N *= 2;
    A.assign(N*2, e);
  }
  Segtree(vector<S> a, S e) : Segtree(a.size(), e) {
    for(int i=0; i<int(a.size()); i++) A[N+i] = a[i];
    for(int i=N-1; i>=1; i--) agg(i);
  }
  S gete(){ return A[0]; }
  S prod(int l, int r){
    l += N; r += N;
    S resl = gete(), resr = gete();
    while(l < r){
      if(l%2) resl = op(resl, A[l++]);
      if(r%2) resr = op(A[--r], resr);
      l /= 2; r /= 2;
    }
    return op(resl, resr);
  }
  void set(int p, S v){
    p += N;
    A[p] = v;
    while(p > 1) agg(p /= 2);
  }
};


int main() {
    cin.tie(0)->sync_with_stdio(0);
    
    int N; cin >> N;
    int Q; cin >> Q;

    vector<S> A(N);
    for(int i=0; i<N; i++){
        cin >> A[i].a.v >> A[i].b.v;
    }

    vector<vector<int>> t(N);
    for(int i=1; i<N; i++){
        int u,v; cin >> u >> v;
        t[u].push_back(v);
        t[v].push_back(u);
    }
    auto hld = HLD(N, t, 0);

    Segtree ds0(N, {1,0});
    Segtree ds1(N, {1,0});

    for(int i=0; i<N; i++) ds0.set(hld.vtos[i], A[i]);
    for(int i=0; i<N; i++) ds1.set(N-1-hld.vtos[i], A[i]);

    for(int i=0; i<Q; i++){
        int ty; cin >> ty;
        if(ty == 0){
            int p; cin >> p;
            S a; cin >> a.a.v >> a.b.v;
            ds0.set(hld.vtos[p], a);
            ds1.set(N-1-hld.vtos[p], a);
        } else {
            int u,v; cin >> u >> v;
            Mint x; cin >> x.v;
            for(auto [l,r] : hld.query(u, v, 0)){
                if(l < r) x = ds0.prod(l, r)(x);
                if(r < l) x = ds1.prod(N-l, N-r)(x);
            }
            cout << x.v << "\n";
        }
    }

    return 0;
}
