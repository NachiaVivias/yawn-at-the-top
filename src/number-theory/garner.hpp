// crt.hpp の inv_mod を使用
// 1 回実行 : ll ans = garner<ll>(md)(rem);
template<class E>
struct garner {
  int n;
  V<ll> m, h;
  garner(V<ll> md) : n(md.size()), m(md), h(n, 1) {
    REP(i,n) REP(j,i) h[i] = h[i] * m[j] % m[i];
    REP(i,n) h[i] = inv_mod(h[i], m[i]);
  }
  E operator()(const V<ll>& r){
    V<ll> a(n, 1), b(n, 0);
    E resa = 1, res = 0;
    REP(k, n) {
      ll t = (r[k] - b[k]) * h[k] % m[k];
      if (t < 0) t += m[k];
      for (int i = k + 1; i < n; ++i) {
        b[i] = (b[i] + t * a[i]) % m[i];
        a[i] = a[i] * m[k] % m[i];
      }
      res = res + E(t) * resa;
      resa = resa * E(m[k]);
    }
    return res;
  }
};
// 連立合同式の mod が互いに素になるように変形
// 返り値 : 解ありなら 1 、解なしなら 0
bool coprimize_mod_system(ll& r1, ll& m1, ll& r2, ll& m2) {
  ll g = gcd(m1, m2);
  if ((r2 - r1) % g) return 0;
  g = gcd(m2 / g, m1);
  while(g > 1) m1 /= g = gcd(g, m1);
  m2 /= gcd(m1, m2);
  r1 %= m1, r2 %= m2;
  return 1;
}