/// Original: Gifted Infants(Intersect) https://yosupo.hatenablog.com/entry/2019/07/02/122433
int crossLL(L l, L m, P& r) {
  D cr1 = crs(l.vec(), m.vec()), cr2 = crs(l.vec(), l.t - m.s);
  if (sgncrs(l.vec(), m.vec()) == 0) {
    r = l.s;
    return sgncrs(l.vec(), l.t - m.s) ? 0 : -1;
  }
  r = m.s + m.vec() * cr2 / cr1;
  return 1;
}
int crossSS(L l, L m, P& r) {
  int u = crossLL(l, m, r);
  if (u == 0) return 0;
  if (u == -1) {
    r = max(min(l.s, l.t), min(m.s, m.t));
    P q = min(max(l.s, l.t), max(m.s, m.t));
    return (q < r) ? 0 : (q == r ? 1 : -1);
  }
  return ccw(l, r) == 0 && ccw(m, r) == 0 ? 1 : 0;
}
