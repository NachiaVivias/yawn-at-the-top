template<class Coord>
struct TwoDRectangleQuery{
  int n, lg;
  V<V<int>> L, idx;
  V<int> Z, rx;
  V<Coord> xs, ys;
  TwoDRectangleQuery(){}
  TwoDRectangleQuery(V<pair<Coord, Coord>> pos)
    : n(pos.size()), lg(countr_zero(bit_ceil(unsigned(n))))
    , L(lg, V<int>(n + 1)), idx(lg+1, V<int>(n,-1)), Z(lg), rx(n), xs(n), ys(n)
  {
    V<pair<Coord, int>> iy(n), ix(n);
    REP(i, n) ix[i] = { pos[i].first, i };
    REP(i, n) iy[i] = { pos[i].second, i };
    sort(iy.begin(), iy.end());
    sort(ix.begin(), ix.end());
    REP(i, n) xs[i] = ix[i].first;
    REP(i, n) rx[ix[i].second] = i;
    REP(i, n) tie(ys[i], idx[lg][i]) = iy[i];
    for (int i = lg - 1; i >= 0; i--) {
      int h = 1 << i;
      auto& prei = idx[i + 1];
      Z[i] = (n >> (i + 1) << i) + min(h, n % (h * 2));
      int ai = 0, bi = Z[i];
      REP(k, n) {
        bool cb = rx[prei[k]] & h;
        idx[i][cb ? bi++ : ai++] = prei[k];
        L[i][k + 1] = L[i][k] + !cb;
      }
    }
    REP(i, n) rx[idx[lg][i]] = i;
  }
// clang-format off
  struct Pt{ int d, i; };
// clang-format on
  V<Pt> getUpdatePoints(int v) {
    V<Pt> q(lg+1, {lg, rx[v]});
    for(auto [d,p] = q[0]; d--; ){
      int h = L[d][p];
      q[d] = {d, p = L[d][p + 1] == h ? Z[d] + p - h : h};
    }
    return q;
  }
// clang-format off
  struct Range{ int d, l, r; };
// clang-format on
  void rec(V<Range>& dest, int l, int r, int yl, int yr, int a, int b, int d){
    if(r <= a || b <= l || yl == yr) return;
    if(l <= a && b <= r){
      dest.push_back({ d, yl, yr });
      return;
    }
    int xm = a + (1 << --d);
    int s = L[d][yl], t = L[d][yr];
    rec(dest, l, r, s, t, a, xm, d);
    rec(dest, l, r, Z[d] + yl - s, Z[d] + yr - t, xm, b, d);
  }
  V<Range> getRanges(Coord xl, Coord xr, Coord yl, Coord yr){
    V<Range> res;
    rec(res,
      lower_bound(xs.begin(), xs.end(), xl) - xs.begin(),
      lower_bound(xs.begin(), xs.end(), xr) - xs.begin(),
      lower_bound(ys.begin(), ys.end(), yl) - ys.begin(),
      lower_bound(ys.begin(), ys.end(), yr) - ys.begin(),
      0, n, lg
    );
    return res;
  }
};