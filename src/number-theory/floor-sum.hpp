/// BEGIN https://github.com/NachiaVivias/yawn-at-the-top/blob/main/src/number-theory/floor-sum.hpp
ll gauss_sum(ll n, ll a, ll b, ll m) {
  ll res = 0;
  while(n) {
    res += a / m * (n * (n - 1) / 2);
    a %= m;
    res += b / m * n;
    b %= m;
    ll y = a * n + b;
    n = y / m;
    b = y % m;
    y = a, a = m, m = y;
  }
  return res;
}
/// END https://github.com/NachiaVivias/yawn-at-the-top/blob/main/src/number-theory/floor-sum.hpp
