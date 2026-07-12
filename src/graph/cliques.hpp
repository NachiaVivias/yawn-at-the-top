// 計算量は O( V^2 + V 2 ^ sqrt(2E) )
// 空集合は含まれない
// void f(const V<int>& clique);
void cliques(int n, V<V<int>> graph, auto f){
  V<V<int>> g(n, V<int>(n));
  REP(x,n) for(auto y : graph[x]) g[x][y] = 1;
  V<int> deg(n);
  REP(i, n) REP(j, n) deg[i] += g[i][j];
  REP(it, n){
    int v = 0;
    REP(i, n) if(deg[i] < deg[v]) v = i;
    V<int> H, C = {v}, F(deg[v]);
    for(int w : graph[v])
      if(deg[w]-- < n) H.push_back(w);
    REP(i, deg[v]) REP(j, i) F[j] |= g[H[i]][H[j]] << i;
    auto dfs = [&](auto& dfs, int m) -> void {
      f(C);
      REP(i, deg[v]) if(m & 1 << i){
        C.push_back(H[i]);
        dfs(dfs, (m -= 1 << i) & F[i]);
        C.pop_back();
      }
    };
    dfs(dfs, (1 << deg[v]) - 1);
    deg[v] = n * 5;
  }
}