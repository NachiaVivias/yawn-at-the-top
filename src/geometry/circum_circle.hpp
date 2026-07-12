/// Original: Gifted Infants(Circle) https://yosupo.hatenablog.com/entry/2019/07/02/122433
C circum_circle(P a, P b, P c) {
  b -= a;
  c -= a;
  D s = 2 * crs(b, c);
  P x = {b.x, c.x};
  P y = {b.y, c.y};
  P z = {b.norm(), c.norm()};
  P r = P{crs(z, y), crs(x, z)} / s;
  return C(r + a, r.abs());
}
C smallest_circle(V<P>& p, int i, array<P, 3> q, int j) {
  if (i == int(p.size())) {
    if(j == 0) return C(P(0, 0), -1);
    if(j == 1) return C(q[0], 0);
    if(j == 2) return C((q[0] + q[1]) / D(2.0),
                 (q[0] - q[1]).abs() / D(2.0));
    if(j == 3) return circum_circle(q[0], q[1], q[2]);
    assert(false);
  }
  C c = smallest_circle(p, i + 1, q, j);
  if (sgn((p[i] - c.p).abs(), c.r) == 1) {
    q[j] = p[i];
    return smallest_circle(p, i + 1, q, j + 1);
  }
  return c;
}
C smallest_circle(V<P> p) {
  random_shuffle(begin(p), end(p));
  return smallest_circle(p, 0, array<P, 3>(), 0);
}