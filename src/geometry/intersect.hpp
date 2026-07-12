/// Original: Gifted Infants(Intersect) https://yosupo.hatenablog.com/entry/2019/07/02/122433
P project(L l, P p) {
  P v = l.vec();
  return l.s + v * dot(v, p - l.s) / v.norm();
}
bool insSL(L s, L l) {
  int a = ccw(l, s.s), b = ccw(l, s.t);
  return a % 2 == 0 || b % 2 == 0 || a != b;
}
bool insSS(L s, L t) {
  int a = ccw(s, t.s), b = ccw(s, t.t);
  int c = ccw(t, s.s), d = ccw(t, s.t);
  return a * b <= 0 && c * d <= 0;
}
D distLP(L l, P p) {
  return abs(crs(l.vec(), p - l.s)) / l.abs();
}
D distSP(L s, P p) {
  P q = project(s, p);
  if (ccw(s, q) == 0) return (p - q).abs();
  return min((s.s - p).abs(), (s.t - p).abs());
}
D distSS(L s, L t) {
  if (insSS(s, t)) return 0;
  return min({distSP(s, t.s), distSP(s, t.t), distSP(t, s.s),
              distSP(t, s.t)});
}
