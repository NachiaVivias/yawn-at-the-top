// オイラー路を一つ構築して { 頂点列 , 辺列 } を返す
pair<V<int>, V<int>> eulerian_trail(
    int N, const V<pair<int, int>>& edges, bool directed, int start = -1) {
  int M = edges.size();
  if(!M) return { {0}, {} };
  V<int> X(M), D(N);
  V<V<int>> G(N);
  REP(m,M){
    auto [u,v] = edges[m];
    G[u].push_back(m);
    if (!directed) G[v].push_back(m);
    X[m] = u + v;
  }
  if(start < 0) {
    start = edges[0].first;
    for(auto [u,v] : edges){
      D[u] += 1;
      D[v] += directed ? -1 : 1;
    }
    REP(i, N) if(D[i] % 2 == 1) start = i;
  }
  V<int> H(M+1,start), E(M), U(M, 0), K(N);
  REP(i,N) K[i] = G[i].size();
  int p = 0, q = M;
  while (q) {
    int v = H[p];
    while (0 < K[v]-- && U[G[v][K[v]]]) ;
    if (K[v] < 0) {
      if (!p) return {{-1}, {-1}};
      H[q--] = H[p--];
      E[q] = E[p];
    } else {
      auto e = G[v][K[v]];
      U[e] = 1;
      E[p++] = e;
      H[p] = X[e] - v;
    }
  }
  REP(i, M) if(X[E[i]] != H[i] + H[i + 1]) return { {-1}, {-1} };
  return {H, E};
}
