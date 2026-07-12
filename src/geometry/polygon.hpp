/// Original: Gifted Infants(Polygon) https://yosupo.hatenablog.com/entry/2019/07/02/122433
using Pol = V<P>;
D area2(const Pol& pol) {
  D u = 0;
  if (!pol.size()) return u;
  P a = pol.back();
  for (auto b : pol) u += crs(a, b), a = b;
  return u;
}
// 0: outside, 1: on line, 2: inside
int contains(const Pol& pol, P p) {
  if (!pol.size()) return 0;
  int in = -1;
  P _a, _b = pol.back();
  for (auto now : pol) {
    _a = _b;
    _b = now;
    P a = _a, b = _b;
    if (ccw(a, b, p) == 0) return 1;
    if (a.y > b.y) swap(a, b);
    if (!(a.y <= p.y && p.y < b.y)) continue;
    if (sgn(a.y, p.y) ? (crs(a - p, b - p) > 0) : (a.x > p.x))
      in *= -1;
  }
  return in + 1;
}

// 以下 cross_point.hpp が必要

Pol convex_cut(const Pol& po, L l) {
  if (!po.size()) return Pol{};
  Pol q;
  P a, b = po.back();
  for (auto now : po) {
    a = b;
    b = now;
    if ((ccw(l, a) % 2) * (ccw(l, b) % 2) < 0) {
      P buf;
      crossLL(l, L(a, b), buf);
      q.push_back(buf);
    }
    if (ccw(l, b) != -1) q.push_back(b);
  }
  return q;
}
// (1:left) | (2: right) is inside between v[i] ~ v[i + 1]
V<pair<P, int>> insPolL(Pol pol, L l) {
  using Pi = pair<P, int>;
  V<Pi> v;
  P a, b = pol.back();
  for (auto now : pol) {
    a = b;
    b = now;
    P p;
    if (crossLL({a, b}, l, p) != 1) continue;
    int sa = ccw(l, a) % 2, sb = ccw(l, b) % 2;
    if (sa > sb) swap(sa, sb);
    if (sa != 1 && sb == 1) v.push_back({p, 1});
    if (sa == -1 && sb != -1) v.push_back({p, 2});
  }
  sort(v.begin(), v.end(), [&](Pi x, Pi y) {
    return dot(l.vec(), x.first - l.s) <
           dot(l.vec(), y.first - l.s);
  });
  int m = int(v.size());
  V<Pi> res;
  for (int i = 0; i < m; i++) {
    if (i) v[i].second ^= v[i - 1].second;
    if (!res.empty() && res.back().first == v[i].first)
      res.pop_back();
    res.push_back(v[i]);
  }
  return res;
}
