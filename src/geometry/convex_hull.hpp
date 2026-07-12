/// Original: Gifted Infants(Polygon) https://yosupo.hatenablog.com/entry/2019/07/02/122433
// p must be sorted and uniqued!
V<P> convex_down(V<P> ps, bool on_edge = 0) {
  assert(ps.size() >= 2);
  int r = -1, f = !on_edge;
  for (P d : ps) {
    while(r > 0 && ccw(ps[r - 1], ps[r], d) % 2 < f) r--;
    ps[++r] = d;
  }
  ps.resize(r + 1);
  return ps;
}
// counter-clockwise
V<P> convex(V<P> ps, bool on_edge = 0) {
  sort(ps.begin(), ps.end());
  ps.erase(unique(ps.begin(), ps.end()), ps.end());
  if (ps.size() <= 1) return ps;
  auto dw = convex_down(ps, on_edge);
  reverse(ps.begin(), ps.end());
  auto up = convex_down(ps, on_edge);
  dw.insert(dw.begin(), up.begin() + 1, up.end() - 1);
  return dw;
}