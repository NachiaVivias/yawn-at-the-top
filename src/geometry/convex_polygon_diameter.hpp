/// Original: Gifted Infants(Polygon) https://yosupo.hatenablog.com/entry/2019/07/02/122433
D diameter(const V<P>& p) {
  int n = int(p.size());
  if (n == 2) return (p[1] - p[0]).abs();
  int x = 0, y = 0;
  for (int i = 1; i < n; i++) {
    if (p[i] < p[x]) x = i;
    if (p[y] < p[i]) y = i;
  }
  D ans = 0;
  int sx = x, sy = y;
  /*
  do {
  ...
  } while (sx != x || sy != y);
  で1周する
  */
  while (sx != y || sy != x) {
    ans = max(ans, (p[x] - p[y]).abs());
    int nx = (x + 1 < n) ? x + 1 : 0,
        ny = (y + 1 < n) ? y + 1 : 0;
    if (crs(p[nx] - p[x], p[ny] - p[y]) < 0)
      x = nx;
    else
      y = ny;
  }
  return ans;
}