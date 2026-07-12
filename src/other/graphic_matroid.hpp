/// Original : Nachia
/// https://atcoder.jp/contests/abc399/submissions/77134460
struct GraphicMatroid {
  V<ll> d, q, g, p, pe;
  ll rt(ll v){ return q[v] >= 0 ? q[v] = rt(q[v]) : v; }
  GraphicMatroid(ll n, V<tuple<ll,ll,ll>> base)
    : d(n), q(n, -1), g(n, -1), p(n, -1), pe(n)
  {
    V<V<pair<ll, ll>>> t(n);
    for(auto [u,v,e] : base){
      t[u].push_back({v, e});
      t[v].push_back({u, e});
    }
    auto dfs = [&](auto& dfs, ll v) -> void {
      for(auto [w, e] : t[v]) if(p[v] != w){
        p[w] = v;
        pe[w] = e;
        d[w] = d[v] + 1;
        g[w] = g[v];
        dfs(dfs, w);
      }
    };
    REP(s, n) if(g[s] < 0) dfs(dfs, g[s] = s);
  }
  V<ll> circuit(ll v, ll w){
    if(g[v] != g[w]) return {-1};
    V<ll> res;
    while((v = rt(v)) != (w = rt(w))){
      if(d[v] < d[w]) swap(v, w);
      res.push_back(pe[v]);
      q[v] = p[v];
    }
    return res;
  }
};