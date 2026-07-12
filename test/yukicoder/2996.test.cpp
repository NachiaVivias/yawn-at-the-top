#define PROBLEM "https://yukicoder.me/problems/no/2996"

/*

No.2996 Floor Sum

( Σ_{i=0}^N i^P ⌊(Ai+B)/M​⌋^Q ) mod 998244353

*/



#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = 1ll << 60;
#define REP(i,n) for(ll i=0; i<ll(n); i++)
template <class T> using V = vector<T>;
template <class A, class B> void chmax(A& l, const B& r){ if(l < r) l = r; }
template <class A, class B> void chmin(A& l, const B& r){ if(r < l) l = r; }

#include "src/number-theory/floor_sum_monoid.hpp"

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

struct Unit {
    ll x;
    ll y;
    ll P;
    ll Q;
    vector<Mint> A;
    Mint& at(ll p, ll q){ return A[p * Q + q]; }
    Mint at(ll p, ll q) const { return A[p * Q + q]; }
};

vector<Mint> ifact, fact;


Unit shiftX(const Unit& r, ll x){
    ll P = r.P, Q = r.Q;
    Unit res = { r.x, r.y, P, Q, vector<Mint>(P*Q) };
    vector<Mint> Z(P,1);
    REP(i,P-1) Z[i+1] = Z[i] * (x-i);
    REP(i,P) Z[i] *= ifact[i];
    REP(p,P) REP(q,Q) REP(pp,P-p) res.at(p+pp,q) += r.at(p,q) * Z[pp];
    return res;
}
Unit shiftY(const Unit& r, ll x){
    ll P = r.P, Q = r.Q;
    Unit res = { r.x, r.y, P, Q, vector<Mint>(P*Q) };
    vector<Mint> Z(Q,1);
    REP(i,Q-1) Z[i+1] = Z[i] * (x-i);
    REP(i,Q) Z[i] *= ifact[i];
    REP(p,P) REP(q,Q) REP(qq,Q-q) res.at(p,q+qq) += r.at(p,q) * Z[qq];
    return res;
}

Unit merge(const Unit& l, const Unit& r){
    ll P = min(l.P, r.P), Q = min(l.Q, r.Q);
    Unit res = { l.x + r.x, l.y + r.y, P, Q };
    res.A.resize(P * Q);
    REP(p,P) REP(q,Q) res.at(p,q) = r.at(p,q);
    res = shiftX(res, l.x);
    res = shiftY(res, l.y);
    REP(p,P) REP(q,Q) res.at(p,q) += l.at(p,q);
    return res;
}

void testcase(){
    ll P, Q, N, M, A, B; cin >> P >> Q >> N >> M >> A >> B;
    ll offset_B = B / M; B %= M;
    if(B < 0){ offset_B -= 1; B += M; }
    ll neg = A < 0 ? -1 : 1;
    if(neg == -1){ B = M - 1 - B; A = -A; }
    N += 1;
    Unit X = Unit{ 1, 0, P+1, Q+1, vector<Mint>((P+1)*(Q+1)) };
    Unit Y = Unit{ 0, neg, P+1, Q+1, vector<Mint>((P+1)*(Q+1)) };
    X.at(0,0) = 1;
    vector<Mint> F(P+1); F[0] = 1;
    REP(i,P) for(ll j=i; j>=0; j--){ F[j+1] += F[j]; F[j] *= j; }
    vector<Mint> G(Q+1); G[0] = 1;
    REP(i,Q) for(ll j=i; j>=0; j--){ G[j+1] += G[j]; G[j] *= j; }
    auto e = Unit{ 0, 0, P+1, Q+1, vector<Mint>((P+1)*(Q+1)) };
    auto buf = FloorSumMonoid<ll, Unit, merge>(N, M, A, B, X, Y, e);
    buf = shiftY(buf, offset_B);
    Mint ans = 0;
    REP(i,P+1) REP(j,Q+1) ans += buf.at(i, j) * fact[i] * fact[j] * F[i] * G[j];
    cout << ans.v << "\n";
}

int main(){
  cin.tie(0)->sync_with_stdio(0);
  ll Z = 100;
  ifact.assign(Z+1, 1);
  for(ll i=1; i<=Z; i++) ifact[i] = ifact[i-1] / i;
  fact.assign(Z+1, 1);
  for(ll i=1; i<=Z; i++) fact[i] = fact[i-1] * i;
  ll T; cin >> T; REP(t,T) testcase();
  return 0;
}
