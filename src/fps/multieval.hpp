template <class Mint>
struct MultiEval {
  int n;
  V<V<Mint>> H;
  MultiEval(V<Mint> p) : n(p.size()), H(n * 2){
    REP(i, n) H[n+i] = { 1, -p[i] };
    for(int i=n-1; i>=1; i--)
      H[i] = multiply(H[i*2], H[i*2+1]);
  }
  V<Mint> query(V<Mint> pol){
    if (!n) return {};
    V<V<Mint>> G(n * 2);
    auto buf = Poly(H[1]).inv(pol.size()).v;
    pol.resize(pol.size() + n - 1);
    G[1] = tr_multiply(buf, pol);
    for(int i=2; i<n * 2; i++)
      G[i] = tr_multiply(H[i ^ 1], G[i / 2]);
    REP(i, n) G[1][i] = G[n + i][0];
    return G[1];
  }
};