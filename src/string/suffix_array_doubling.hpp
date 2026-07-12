template <class Str>
V<ll> suffix_array(Str s) {
  ll n = s.size();
  V<ll> sa(n), rsa(n), tmp(n);
  REP(i, n) sa[i] = i;
  REP(i, n) rsa[i] = s[i]; // 必要ならここで座圧
  for (ll k = 1; k < n; k *= 2) {
    auto cmp = [&](ll x, ll y) {
      if (rsa[x] != rsa[y]) return rsa[x] < rsa[y];
      ll rx = x + k < n ? rsa[x + k] : -1;
      ll ry = y + k < n ? rsa[y + k] : -1;
      return rx < ry;
    };
    sort(sa.begin(), sa.end(), cmp);
    tmp[sa[0]] = 0;
    REP(i, n - 1) tmp[sa[i + 1]] = tmp[sa[i]] + cmp(sa[i], sa[i + 1]);
    REP(i, n) rsa[i] = tmp[i];
  }
  return sa;
}