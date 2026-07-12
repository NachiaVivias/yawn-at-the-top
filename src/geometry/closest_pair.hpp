tuple<D, int, int> cp_rec(vector<pair<P, int>>& psi, int l,
                          int r) {
  if (l + 1 == r) return {1e100, -1, -1};
  int m = midpoint(l, r);
  D x = psi[m].first.x;
  auto dd = min(cp_rec(psi, l, m), cp_rec(psi, m, r));
  auto [d, di, dj] = dd;
  inplace_merge(
      psi.begin() + l, psi.begin() + m, psi.begin() + r,
      [&](auto a, auto b) { return a.first.y < b.first.y; });
  vector<int> pp;
  for (int a = l; a < r; a++) {
    auto [p, i] = psi[a];
    if (p.x <= x - d || x + d <= p.x) continue;
    for (int b : pp | views::reverse) {
      auto [q, j] = psi[b];
      D dx = p.x - q.x, dy = p.y - q.y;
      if (dy >= d) break;
      D nd = sqrt(dx * dx + dy * dy);
      if (d > nd) d = nd, di = i, dj = j;
    }
    pp.push_back(a);
  }
  return {d, di, dj};
}
tuple<D, int, int> closest_pair(const vector<P>& ps) {
  int n = ssize(ps);
  vector<pair<P, int>> psi(n);
  REP(i, n) psi[i] = {ps[i], i};
  sort(psi.begin(), psi.end(),
       [](auto a, auto b) { return a.first.x < b.first.x; });
  return cp_rec(psi, 0, n);
}
