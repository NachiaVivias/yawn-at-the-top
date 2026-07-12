// 辺は配列 E に一列に並んでいる。
// 辺 e (e : int) の逆辺は、辺 e^1 である。
struct MCF {
  using Cap = ll;
  using Cost = ll;
  Cost INF = 1ll << 60;
  struct Edge {
    int from;
    int to;
    Cost cost;
    Cap cap;
  };
  int N;
  V<Edge> E;
  V<V<int>> g;
  V<Cost> P;
  MCF(int n) : N(n), g(n), P(n, 0) {
  }
  int addEdge(int u, int v, Cap cap, Cost cost) {
    int e = E.size();
    g[u].push_back(e);
    g[v].push_back(e + 1);
    E.push_back({u, v, cost, cap});
    E.push_back({v, u, -cost, 0});
    return e;
  }
  pair<Cap, Cost> flowuni(int s, int t, Cap lim) {
    V<Cost> dist(N, INF);
    V<int> par(N, -1);
    V<Cap> fl(N, lim);
    priority_queue<pair<Cost, int>> que;
    dist[s] = 0;
    que.push({0, s});
    while (que.size()) {
      auto [d, v] = que.top();
      que.pop();
      if (dist[v] != -d) continue;
      if (v == t) break;
      for (auto e : g[v])
        if (E[e].cap) {
          int w = E[e].to;
          Cost nd = -d + P[v] + E[e].cost - P[w];
          if (dist[w] <= nd) continue;
          dist[w] = nd;
          que.push({-nd, w});
          par[w] = e;
          fl[w] = min(fl[v], E[e].cap);
        }
    }
    if (par[t] < 0) return {0, 0};
    lim = fl[t];
    for (int p = t; p != s;) {
      int e = par[p];
      E[e].cap -= lim;
      E[e ^ 1].cap += lim;
      p = E[e ^ 1].to;
    }
    for (int i = 0; i < N; i++)
      if (i == s || par[i] >= 0) {
        P[i] += dist[i] - dist[t];
      }
    return {P[t] - P[s], lim};
  }
  V<pair<Cap, Cost>> slope(int s, int t, Cap lim) {
    V<pair<Cap, Cost>> res;
    res.push_back({0, 0});
    Cap fl = 0;
    Cost co = 0;
    while (fl < lim) {
      auto [u, v] = flowuni(s, t, lim - fl);
      if (v == 0) break;
      res.push_back({fl += v, co += u * v});
    }
    return res;
  }
  pair<Cap, Cost> flow(int s, int t, Cap lim) {
    return slope(s, t, lim).back();
  }
};
