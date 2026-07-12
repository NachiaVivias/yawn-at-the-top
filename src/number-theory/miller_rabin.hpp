/// Original: Gifted Infants(Prime) https://yosupo.hatenablog.com/entry/2019/07/02/122433
bool is_prime(ll n) {
  if (n <= 1) return 0;
  if (n % 2 == 0) return n == 2;
  ll d = n - 1;
  while (d % 2 == 0) d /= 2;
  /// n < 4759123141 なら {2, 7, 61}
  /// n < 341550071728321なら{17以下の素数} で十分
  // n < 4.7e9 なら {2, 7, 61}
  // n < 3.4e14なら{17以下の素数} で十分
  for (ll a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
    if (n <= a) break;
    ll t = d, y = pow_mod<__int128_t>(a, t, n);  // over
    for (; t != n - 1 && y != 1 && y != n - 1; t *= 2)
      y = __int128_t(y) * y % n;  // flow
    if (y != n - 1 && t % 2 == 0) return 0;
  }
  return 1;
}
ll pollard_single(ll n) {
  if (n % 2 == 0) return 2;
  /// 怪しげなヒューリスティックではある
  /// 実際、 2 の倍数では確実に失敗する
  REP(st, n) if(st) {
    auto f = [&](ll x) { return (__int128_t(x) * x + st) % n; };
    ll x = st, y = f(x), p;
    while ((p = gcd((y - x + n), n)) != n) {
      if (p != 1) return p;
      x = f(x), y = f(f(y));
    }
  }
}
V<ll> pollard(ll n) {
  if (n == 1) return {};
  if (is_prime(n)) return {n};
  ll x = pollard_single(n);
  auto res = pollard(x);
  for(auto a : pollard(n / x)) res.push_back(a);
  return res;
}