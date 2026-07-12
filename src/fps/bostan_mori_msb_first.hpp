// res[i] = 1/d の N-i 次の係数
template <class D>
V<D> bostan_mori_sub(V<D> d, ll N) {
  int k = d.size();
  if(!N) {
    V<D> res(k);
    res[0] = d[0].inv();
    return res;
  }
  V<D> nd(k + 1), q(k * 2);
  REP(i, k) nd[i] = i % 2 ? -d[i] : d[i];
  auto h = multiply(d, nd);
  REP(i, k) h[i] = h[i * 2];
  h.resize(k);
  h = bostan_mori_sub(move(h) , N / 2);
  REP(i, k) q[i * 2 + N % 2] = h[i];
  return tr_multiply(move(nd), move(q));
}
// res[i] = n/d の N+i 次の係数
template <class D>
V<D> bostan_mori(V<D> n, V<D> d, ll N, int m) {
  auto inv = [](V<D> f, int m){
    f.resize(m * 2);
    V<D> q = { f[0].inv() };
    for(int z=2; z/2<m; z*=2){
      auto g = multiply(q, q);
      g = multiply(g, V<D>(f.begin(), f.begin() + z));
      q.resize(z);
      REP(i, z) q[i] += q[i] - g[i];
    }
    q.resize(m);
    return q;
  };
  int k = max(n.size(), d.size());
  n.resize(k);
  d.resize(k);
  auto f = bostan_mori_sub(d, N);
  reverse(f.begin(), f.end());
  reverse(n.begin(), n.end());
  f = multiply(f, d);
  f.resize(k);
  f = multiply(f, inv(d, k + m - 1));
  f.resize(k + m - 1);
  return tr_multiply(n, f);
}