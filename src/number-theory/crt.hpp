/// Original: Gifted Infants (数学) (https://yosupo.hatenablog.com/entry/2019/07/02/122433)
/// g:gcd(a, b), ax+by=g
struct EG { ll g, x, y; };
EG ext_gcd(ll a, ll b) {
  if(!b) return a >= 0 ? EG{a, 1, 0} : EG{-a, -1, 0};
  auto e = ext_gcd(b, a % b);
  return EG{e.g, e.y, e.x - a / b * e.y};
}
ll inv_mod(ll x, ll md) {
  return (ext_gcd(x, md).x % md + md) % md;
}
template <class T, class U>
T pow_mod(T x, U n, T md) {
  T r = 1 % md;
  x %= md;
  while (n) {
    if (n & 1) r = (r * x) % md;
    x = (x * x) % md;
    n >>= 1;
  }
  return r;
}
pair<ll, ll> crt(const V<ll>& b, const V<ll>& c) {
  ll r = 0, m = 1;
  REP(i, b.size()) {
    auto eg = ext_gcd(m, c[i]);
    ll g = eg.g, im = eg.x;
    if ((b[i] - r) % g) return {0, -1};
    ll tmp = (b[i] - r) / g * im % (c[i] / g);
    r += m * tmp;
    m *= c[i] / g;
  }
  return {(r % m + m) % m, m};
}
