struct HLD {
  int N;
  int g;
  V<V<int>> t;
  V<int> par, dep, sz, pp, stov, vtos, px, index;
  HLD(int N, V<V<int>> graph, int root)
      : N(N), g(0), t(move(graph)), par(N, -1),
      dep(N), sz(N, 1), pp(N), stov(N), vtos(N),
      px(N), index(N) {
    dfs1(root);
    dfs2(root);
  }
  void dfs1(int v) {
    for (auto& w : t[v]){
      t[w].erase(find(t[w].begin(), t[w].end(), v));
      par[w] = v;
      dep[w] = dep[v] + 1;
      dfs1(w);
      sz[v] += sz[w];
      if(sz[t[v][0]] < sz[w]) swap(t[v][0], w);
    }
  }
  void dfs2(int v) {
    vtos[v] = g;
    stov[g++] = v;
    for (auto w : t[v]){
      int f = w == t[v][0];
      pp[w] = f ? pp[v] : w;
      px[w] = px[v] + 1 - f;
      dfs2(w);
    }
  }
  int lca(int a, int b) {
    if (px[pp[a]] > px[pp[b]]) swap(a, b);
    while (px[pp[a]] < px[pp[b]]) b = par[pp[b]];
    while (pp[a] != pp[b]) {
      a = par[pp[a]];
      b = par[pp[b]];
    }
    return dep[a] < dep[b] ? a : b;
  }
  auto query_half(int r, int a, bool edge = false) {
    vector<pair<int,int>> res(px[a] - px[r] + 1);
    while (px[a] > px[r]) {
      res[px[a] - px[r]] = { vtos[pp[a]], vtos[a] + 1 };
      a = par[pp[a]];
    }
    res[0] = { vtos[r] + edge, vtos[a] + 1 };
    return res;
  }
  // return vector<pair<int,int>>
  // a -> b
  // l<rなら[l:r)、l>rなら[r:l)の逆順
  // edge=trueの場合はlcaを含まない区間を返す
  auto query(int a, int b, bool edge = false) {
    int g = lca(a, b);
    auto l = query_half(g, b, edge);
    auto r = query_half(g, a, 1);
    for(auto& q : r) swap(q.first, q.second);
    l.insert(l.begin(), r.rbegin(), r.rend());
    return l;
  }
  // 返り値は縮約後の縮約後の頂点集合 vector<int> と
  // 木の辺の集合 vector<pair<int,int>> !! もとの頂点番号 !!
  // もし reindex したいなら index[v] を見ればいい
  pair<V<int>, V<pair<int, int>>> ComputeTree(V<int> vs) {
    auto comp = [&](int x, int y) { return vtos[x] < vtos[y]; };
    sort(vs.begin(), vs.end(), comp);
    int K = vs.size();
    REP(i, K - 1) vs.push_back(lca(vs[i], vs[i + 1]));
    sort(vs.begin(), vs.end(), comp);
    vs.erase(unique(vs.begin(), vs.end()), vs.end());
    K = vs.size();
    REP(i, K) index[vs[i]] = i;
    V<pair<int, int>> es;
    REP(i, K - 1) es.push_back({ lca(vs[i], vs[i + 1]), vs[i + 1] });
    return {vs, es};
  }
};