/// Original : Gifted Infants(DisjointTable) https://yosupo.hatenablog.com/entry/2019/07/02/122433
template <class S, S op(S, S), S e()>
struct DisjointTable {
  V<V<S>> a;
  DisjointTable(V<S> v = {}) {
    int lg = 1, n = 2;
    while (n < ssize(v)) lg++, n *= 2;
    v.resize(n, e());
    a.assign(lg, V<S>(n, e()));
    a[0] = v;
    REP(h,lg) if(h) {
      int u = 1 << h;
      for(int m=u; m<n; m+=2*u){
        S q = e();
        REP(i,u) a[h][m-i-1] = q = op(v[m-i-1], q);
        q = e();
        REP(i,u) a[h][m+i] = q = op(q, v[m+i]);
      }
    }
  }
  S query(int l, int r) {
    r--;
    if (l > r) return e();
    if (l == r) return a[0][l];
    int u = 31 - countl_zero((unsigned int)(l ^ r));
    return op(a[u][l], a[u][r]);
  }
};