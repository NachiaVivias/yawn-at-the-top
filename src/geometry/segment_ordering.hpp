struct LI {
  L l;
  ll i;
  L reg() const { return l.s < l.t ? l : L{l.t, l.s}; }
  static ll d(P a, P b, P c){
    return c < a || b < c ? 0 : sgncrs(a, b, c);
  }
  bool operator<(LI b) const {
    L l = reg(), r = b.reg();
    if(l.t < r.s || r.t < l.s) return 0;
    ll f = 0;
    f += d(l.s, l.t, r.s) - d(r.s, r.t, l.s);
    f += d(l.s, l.t, r.t) - d(r.s, r.t, l.t);
    if(f) return 0 < f;
    return !(r.s < l.t) && (l.s < r.t || i < b.i);
  }
};
V<ll> orderSegments(V<L> e, ll inf = 1ll << 30){
  ll n = e.size(), f = 0;
  for(auto& l : e) if(l.t < l.s) swap(l.s, l.t);
  V<pair<P, int>> X(n * 2);
  REP(i, n) X[i] = {e[i].s, i};
  REP(i, n) X[n + i] = {e[i].t, n + i};
  V<ll> d(n), res(n), ord(n, -1);
  V<V<ll>> adj(n);
  std::set<LI> ds;
  V<std::set<LI>::iterator> its(n, ds.end());
  ds.insert({{{-inf,-inf}, {inf,-inf}}, -1});
  ds.insert({{{-inf,inf}, {inf,inf}}, -1});
  stable_sort(X.begin(), X.end());
  auto addEdge = [&](ll l, ll r){
    if(l >= 0 && r >= 0) adj[l].push_back(r), d[r]++;
  };
  for(auto [x, i] : X){
    if(i < n){
      its[i] = ds.insert({e[i], i}).first;
      auto l = its[i], r = its[i];
      addEdge((--l)->i, i), addEdge(i, (++r)->i);
    } else {
      i -= n;
      auto l = its[i], r = its[i];
      addEdge((--l)->i, (++r)->i);
      ds.erase(its[i]);
    }
  }
  REP(i, n) if(!d[i]) ord[f++] = i;
  for(ll v : ord) if(v >= 0) for(ll w : adj[v]) if(!--d[w]) ord[f++] = w;
  REP(i, n) res[ord[i]] = i;
  return res;
}