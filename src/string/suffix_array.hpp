/// Original: AtCoder Library
V<ll> sa_is(auto s, ll B = 200) {
  ll n = s.size(), m = 0, b = 0;
  if (n <= 1) return {0};
  V<ll> a(n + 1, -1), sa(n), ls(n);
  REP(i, n) a[i] = s[i];
  for (ll i = n - 2; i >= 0; i--)
    ls[i] = a[i] < a[i + 1] || a[i] == a[i + 1] && ls[i + 1];
  auto induce = [&](const V<ll>& lms) {
    REP(i, n) sa[i] = -1;
    V<ll> zs(B + 1), zl(B + 2), yl(B + 2);
    REP(i, n) ls[i] ? zl[a[i] + 1]++ : zs[a[i]]++;
    REP(i, B + 1) yl[i] = zl[i + 1] += zs[i] += zl[i];
    REP(i, m) sa[zs[a[lms[i]]]++] = lms[i];
    sa[zl[a[n - 1]]++] = n - 1;
    for(ll v : sa) if (v-- > 0 && !ls[v]) sa[zl[a[v]]++] = v;
    REP(i, n) if (ll v = sa[n - 1 - i]; v-- > 0 && ls[v]) sa[--yl[a[v]]] = v;
  };
  V<ll> f(n + 1, -1), lms(n + 1, n);
  REP(i, n) if (i && !ls[i - 1] && ls[i]) lms[f[i] = m++] = i;
  induce(lms);
  if (m) {
    V<ll> res, nx(m);
    REP(i, n) if (f[sa[i]] >= 0) res.push_back(sa[i]);
    REP(i, m - 1) {
      ll l = res[i], r = res[i + 1];
      ll el = lms[f[l] + 1], er = lms[f[r] + 1];
      while (l < el && r < er && a[l] == a[r]) l++, r++;
      nx[f[res[i + 1]]] = b += l < el || r < er;
    }
    auto q = sa_is(nx, b);
    for (ll& x : q) x = lms[x];
    induce(q);
  }
  return sa;
}