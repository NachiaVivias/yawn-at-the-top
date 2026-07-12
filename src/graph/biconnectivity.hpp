struct Biconnectivity {
  V<pair<int,int>> bct; // ( 2-連結成分の番号, 頂点 )
  V<int> tecc; // tecc[頂点] == 2辺連結成分の番号
  int num_bcc, num_tecc;
  Biconnectivity(int n, const V<V<int>>& g) : tecc(n) {
    V<int> low(n), ord(n, -1), st(n), est(n + 1, n);
    int it = 0, idx = 0, eit = 0, f = 0;
    auto dfs = [&](auto& dfs, int v, int p) -> void {
      st[it] = est[eit++] = v;
      low[v] = ord[v] = it++;
      for(int w : g[v]) if(w != p || !(p = -1)) {
        if(ord[w] < 0){
          dfs(dfs, w, v);
          low[v] = min(low[v], low[w]);
          if(low[w] >= ord[v]){
            while(ord[w] < it) bct.push_back({ idx, st[--it] });
            bct.push_back({ idx++, v });
          }
        }
        low[v] = min(low[v], ord[w]);
      }
      if(low[v] == ord[v] && ++f)
        while(est[eit] != v) tecc[est[--eit]] = f - 1;
    };
    REP(v, n) if(ord[v] < 0) dfs(dfs, v, -1);
    REP(v, n) if(!g[v].size()) bct.push_back({ idx++, v });
    num_bcc = idx;
    num_tecc = f;
  }
};