/// Original: Gifted Infants(Circle) https://yosupo.hatenablog.com/entry/2019/07/02/122433
struct C {
  P p;
  D r;
  C(P p = P(), D r = D()) : p(p), r(r) {
  }
};
// need Intersect/distLP, r.sはよりl.sに近い
int crossCL(C c, L l, L& r) {
  D u = distLP(l, c.p);
  int si = sgn(u, c.r);
  if (si == 1) return 0;
  P v = project(l, c.p);
  P di = (si == 0)
             ? P(0, 0)
             : l.vec() * (sqrt(c.r * c.r - u * u) / l.abs());
  r = L(v - di, v + di);
  if (si == 0) return 1;
  return 2;
}
// need Intersect/distLP, r.sはよりl.sに近い
int crossCS(C c, L s, L& l) {
  if (!crossCL(c, s, l)) return 0;
  bool f1 = !ccw(s, l.s), f2 = !ccw(s, l.t);
  if (f1 && f2) return 2;
  if (!f1 && !f2) return 0;
  if (f1) l.t = l.s; else l.s = l.t;
  return 1;
}
// return number of cross point
// l, rはcから見た交点の角度、[l, r]がdに覆われている
int crossCC(C c, C d, D& l, D& r) {
  if (c.p == d.p) {
    assert(sgn(c.r - d.r));
    // prohibit same circles
    return 0;
  }
  D di = (c.p - d.p).abs(), bth = (d.p - c.p).arg();
  D costh = (c.r * c.r + di * di - d.r * d.r) / (2 * c.r * di);
  int ty = min(sgn(c.r + d.r, di), sgn(di, abs(c.r - d.r)));
  if (ty == -1) return 0;
  if (ty == 0) costh = sgn(costh);
  D th = acos(max(D(-1), min(D(1), costh)));
  l = bth - th;
  r = bth + th;
  return ty + 1;
}
// C(P(0, 0), r)とTri((0, 0), a, b)の共有面積
D area2CT(C c, P _a, P _b) {
  P a = _a - c.p, b = _b - c.p;
  D r = c.r;
  if (a == b) return 0;
  auto single = [&](P x, P y, bool tri) {
    if (tri) return crs(x, y);
    return r * r * ((y * P(x.x, -x.y)).arg());
  };
  bool ia = sgn(a.abs(), r) != 1, ib = sgn(b.abs(), r) != 1;
  if (ia && ib) return single(a, b, true);
  L l;
  if (!crossCS(C(P(0, 0), r), L(a, b), l))
    return single(a, b, false);
  return single(a, l.s, ia) + single(l.s, l.t, true) +
         single(l.t, b, ib);
}
// p, cの共有面積
D area2CPol(C c, const V<P>& po) {
  D sm = 0;
  P a, b = po.back();
  for (auto p : po) {
    a = b;
    b = p;
    sm += area2CT(c, a, b);
  }
  return sm;
}
