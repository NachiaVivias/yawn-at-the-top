template <class D>
struct MultiEval {
  int n;
  V<V<D>> H;
  MultiEval(V<D> p) : n(p.size()), H(n * 2){
    REP(i, n) H[n+i] = { 1, -p[i] };
    for(int i=n-1; i>=1; i--)
      H[i] = multiply(H[i*2], H[i*2+1]);
  }
  V<D> inv(V<D> f, int m){
    f.resize(m * 2);
    V<D> q = {1};
    for(int z=2; z < m * 2; z*=2){
      auto g = multiply(q, q);
      g = multiply(g, V<D>(f.begin(), f.begin() + z));
      q.resize(z);
      REP(i, z) q[i] += q[i] - g[i];
    }
    q.resize(m);
    return q;
  }
  V<D> query(V<D> pol){
    V<V<D>> G(n * 2);
    auto f = inv(H[1], pol.size());
    pol.resize(pol.size() + n - 1);
    G[1] = tr_multiply(f, pol);
    for(int i=2; i<n * 2; i++)
      G[i] = tr_multiply(H[i ^ 1], G[i / 2]);
    REP(i, n) G[1][i] = G[n + i][0];
    return G[1];
  }
};