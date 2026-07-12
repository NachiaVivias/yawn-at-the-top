// f(g(x)) mod x^N (g[0] = 0)
template <class D>
V<D> fps_composition(V<D> f, V<D> g, ll N) {
  ll z = 1;
  while(z < N) z *= 2;
  V<D> p(z * 2), q(z * 3), res(N);
  REP (i, f.size()) p[i * 2] = f[i];
  REP (i, min<ll>(g.size(), z)) q[z * 2 + i] = -g[i];
  q[0] = 1;
  auto dfs = [&](auto& h, V<D> q, ll u, ll v) -> void {
    if(v == z) return;
    ll nu = (u + 1) / 2, nv = v * 2;
    V<D> nq = q, y(nu * 2 * (nv + 1));
    REP(i, q.size()) if (i % 2) nq[i] = -nq[i];
    q = multiply(q, nq);
    REP (d, nv + 1) REP(i, nu) y[d * nu * 2 + i] = q[d * u * 2 + i * 2];
    h(h, move(y), nu, nv);
    V<D> x(u * 2 * (v * 2 + 1) - 1);
    REP (d, nv) REP(i, nu) x[d * u * 2 + i * 2 + 1] = p[d * nu * 2 + i];
    p = tr_multiply(nq, x);
  };
  dfs(dfs, move(q), z, 1);
  REP(i, N) res[i] = p[z - 1 - i];
  return res;
}