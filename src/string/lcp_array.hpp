/// Original: AtCoder Library
V<ll> lcp_array(auto s, V<ll> sa) {
  ll n = s.size(), h = 0;
  V<ll> rsa(n + 1), lcp(n);
  REP(i, n) rsa[sa[i]] = i;
  REP(i, n) {
    if (h > 0) h--;
    if (rsa[i] == n - 1) continue;
    ll j = sa[rsa[i] + 1];
    for (; j + h < n && i + h < n; h++) {
      if (s[j + h] != s[i + h]) break;
    }
    lcp[rsa[i]] = h;
  }
  return lcp;
}