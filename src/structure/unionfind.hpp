struct UnionFind {
  V<int> p;
  int gn;
  UnionFind(int n = 0) : p(n, -1), gn(n) {
  }
  void merge(int a, int b) {
    int x = group(a), y = group(b);
    if (x == y) return;
    gn--;
    if (-p[x] < -p[y]) swap(x, y);
    p[x] += p[y];
    p[y] = x;
  }
  int size(int a) { return -p[group(a)]; }
  int group(int a) {
    if (p[a] < 0) return a;
    return p[a] = group(p[a]);
  }
  bool same(int a, int b) {
    return group(a) == group(b);
  }
};