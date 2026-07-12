// result[i] : use A[i][result[i]]
using Cost = ll;
V<int> AssignmentProblem(
  int n, int m,
  const V<V<Cost>>& A, int K, Cost INF
){
  V<Cost> d(m+1,0), h(m,0);
  V<int> l(n,-1), r(m,-1);
  while(K--){
    V<int> f(m), par(m,-1);
    auto ch = [&](int w, Cost f, int v){
      if(f < d[w]) d[w] = f, par[w] = v;
    };
    REP(v,m+1) d[v] = INF;
    REP(v,n) if(l[v] < 0) REP(w,m)
      ch(w, A[v][w] - h[w], v);
    int w = -1;
    while(1){
      w = m;
      REP(i,m) if(!f[i] && d[i] < d[w]) w = i;
      f[w] = 1;
      if(r[w] < 0) break;
      int v = r[w];
      auto c = d[w] + h[w] - A[v][w];
      REP(x,m) if(!f[x]) ch(x, c + A[v][x] - h[x], v);
    }
    REP(i,m) if(f[i]) h[i] += d[i] - d[w];
    while(w >= 0) swap(w, l[r[w] = par[w]]);
  }
  return l;
}
