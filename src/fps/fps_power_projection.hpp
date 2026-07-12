// [x^K] f(x) / (1 - y g(x)) mod y^N (g[0] = 0)
template <class D>
V<D> power_projection(V<D> f, V<D> g, ll K, ll N) {
  ll u = K + 1, v = 1;
  V<D> p(u * 2 * v), q(u * 2 * (v + 1)), res(N);
  REP (i, min<ll>(f.size(), u)) p[i] = f[i];
  REP (i, min<ll>(g.size(), u)) q[u * 2 + i] = -g[i];
  q[0] = 1;
  while(K || v < N){
    ll nu = (u + 1) / 2, nv = v * 2;
    V<D> nq = q, x(nu * 2 * nv), y(nu * 2 * (nv + 1));
    REP (d, v + 1) REP (i, u) if (i % 2) nq[d * u * 2 + i] *= -1;
    q = multiply(q, nq);
    p = multiply(p, nq);
    REP (d, nv) REP(i, nu)
      x[d * nu * 2 + i] = p[d * u * 2 + i * 2 + K % 2];
    REP (d, nv + 1) REP(i, nu)
      y[d * nu * 2 + i] = q[d * u * 2 + i * 2];
    u = nu, v = nv, K /= 2;
    swap(p, x);
    swap(q, y);
  }
  REP(i,N) res[i] = p[i * 2];
  return res;
}