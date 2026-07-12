/// Original: Gifted Infants(Circle) https://yosupo.hatenablog.com/entry/2019/07/02/122433
// pからcに接線を引く，交点はp1, p2
int tangent(C c, P p, P& p1, P& p2) {
  D di = (c.p - p).abs();
  int si = sgn(c.r, di);
  if (si == 1) return 0;
  D th = acos(min(D(1), c.r / di));
  D ar = (p - c.p).arg();
  p1 = c.p + P::polar(c.r, ar - th);
  p2 = c.p + P::polar(c.r, ar + th);
  if (si == 0) return 1;
  return 2;
}
// 共通接線
int tangent(C c, C d, L& l, L& r, bool inter) {
  D di = (d.p - c.p).abs(), ar = (d.p - c.p).arg();
  if (sgn(di) == 0) {
    assert(sgn(c.r - d.r));
    // prohibit same circles
    return 0;
  }
  D costh = c.r + (inter ? d.r : -d.r);
  int si = sgn(abs(costh), di);
  costh /= di;
  if (si == 1) return 0;
  if (si == 0) costh = sgn(costh);
  D th = acos(max(D(-1), min(D(1), costh)));
  P base;
  base = P::polar(1, ar - th);
  l = L(c.p + base * c.r, d.p + base * d.r * (inter ? -1 : 1));
  base = P::polar(1, ar + th);
  r = L(c.p + base * c.r, d.p + base * d.r * (inter ? -1 : 1));
  if (si == 0) return 1;
  return 2;
}