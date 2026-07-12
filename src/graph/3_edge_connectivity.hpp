struct ThreeEdgeConnectivity{
  int num2, num3;
  V<int> col2, col3;
  ThreeEdgeConnectivity(int n, V<pair<int,int>> G)
    : col3(n, -1), col2(n, -1)
  {
    solve(n, move(G));
  }
  int assignColors(V<int>& a, const V<int>& idx){
    int i = 0;
    for(int v : idx) a[v] = a[v] < 0 ? i++ : a[a[v]];
    return i;
  }
  void solve(int n, V<pair<int,int>> G){
    int m = G.size();
    V<V<int>> inc(n);
    V<int> X(m), par(n, -1), I(n, -1), O(n, 0), low(n, n), deg(n, 0), P(n, -1);
    REP(i, m) {
      auto [u,v] = G[i];
      inc[u].push_back(i);
      inc[v].push_back(i);
      X[i] = u ^ v;
    }
    int dfsid = 0;
    auto absorb = [&](int x, int l, int r){
      while(P[x] >= 0){
        int y = P[x];
        if(l < I[y] || O[y] < r) break;
        deg[x] += deg[y] - 2; deg[y] = 0;
        P[x] = P[y];
        col3[y] = x;
      }
    };
    auto dfs = [&](auto& dfs, int w) -> void {
      I[w] = dfsid++;
      for (int e : inc[w]) if (int u = X[e] ^ w; u != w) {
        deg[w] += 1;
        if(e == par[w]) continue;
        if(I[u] == -1){
          par[u] = e;
          dfs(dfs, u);
        } else if(I[u] < I[w]){
          if(I[u] < low[w]){
            low[w] = I[u];
            absorb(w, n, -1);
          }
        } else {
          absorb(w, I[u], O[u]);
          deg[w] -= 2;
        }
      }
      O[w] = dfsid;
      if(par[w] < 0) return;
      int u = w ^ X[par[w]];
      if(I[u] >= low[w]){
        col2[w] = u;
        int low_w = low[w], buf = P[u];
        if(deg[w] == 2) deg[w] -= 2, w = P[w];
        if(low[u] <= low_w){
          P[u] = w;
          absorb(u, n, -1);
          P[u] = buf;
        } else {
          low[u] = low_w;
          absorb(u, n, -1);
          P[u] = w;
        }
      } else deg[w] -= 1, deg[u] -= 1;
    };
    REP(s, n) if(I[s] == -1) dfs(dfs, s);
    REP(i, n) O[I[i]] = i;
    num2 = assignColors(col2, O);
    num3 = assignColors(col3, O);
  }
};