// res.first = 強連結成分の個数
// res.second[v] = v が属する強連結成分の番号
pair<int, V<int>> scc(int n, V<V<int>> g){
  int tm = 0, it = 0, idx = 0;
  V<int> ord(n, -1), st(n + 1, n), id(n, n);
  auto dfs = [&](auto& dfs, int v) -> int {
    int low = ord[v] = tm++;
    st[it++] = v;
    for (auto w : g[v]) if(id[w] >= n)
      chmin(low, ord[w] < 0 ? dfs(dfs, w) : ord[w]);
    if (low == ord[v] && ++idx)
      while(st[it] != v) id[st[--it]] = idx;
    return low;
  };
  REP(i, n) if (ord[i] == -1) dfs(dfs, i);
  for(auto& x : id) x = idx - x;
  return make_pair(idx, move(id));
}