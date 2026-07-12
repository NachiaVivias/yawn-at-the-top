struct ACNode {
  ll len = 0, li = 0;  // suffix link
  array<ll, 26> nx = {}; // 1 文字足したときの最長接尾辞
};
template<class Str, ll offset = 'a'>
pair<V<ACNode>, V<ll>> AhoCorasick(const V<Str>& s){
  V<ACNode> a(1);
  V<ll> p(s.size()), bfs(s.size());
  REP(i, s.size()) bfs[i] = i;
  REP(i, bfs.size()){
    ll v = bfs[i];
    if(a[p[v]].len == s[v].size()) continue;
    ll &q = p[v], c = s[v][a[q].len] - offset;
    if(a[a[q].nx[c]].len <= a[q].len){
      a.push_back(ACNode());
      a[q].nx[c] = a.size() - 1;
      a.back().len = a[q].len + 1;
    }
    q = a[q].nx[c];
    bfs.push_back(v);
  }
  for(auto& q : a) REP(j, q.nx.size()) if(q.len){
    if(q.nx[j]) a[q.nx[j]].li = a[q.li].nx[j];
    if(!q.nx[j]) q.nx[j] = a[q.li].nx[j];
  }
  return { a, p };
};