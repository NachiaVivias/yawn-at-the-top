template <class X, class S>
ll bsgs(X x, S s, S t, auto op, X xe, auto mapping, ll n) {
  ll m = sqrt(n), k = 0;
  S xit = t, p = s, nxp = s;
  X x2 = x, xm = x;
  unordered_set<S> mp;
  REP(i, m) mp.insert(xit = mapping(x, xit));
  for (ll d = 1; d < m; d *= 2) {
    if ((m - 1) & d) xm = op(xm, x2);
    x2 = op(x2, x2);
  }
  REP(a, 2) {
    while (!mp.contains(nxp = mapping(xm, p))) {
      if (k >= n) return -1;
      p = nxp;
      k += m;
    }
    REP(i, m) {
      if (p == t) return k;
      p = mapping(x, p);
      k++;
    }
  }
  return -1;
}