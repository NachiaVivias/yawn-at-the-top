/// Original: Nyaan's Library https://nyaannyaan.github.io/library/tree/static-top-tree-vertex-based.hpp
struct StaticTopTree {
  static const int VERT = 0; // -1     -1     vtx
  static const int COMP = 1; // root   child  eidx+n
  static const int RAKE = 2; // child  child  -1
  static const int ADDE = 3; // child  -1     eidx+n
  static const int ADDV = 4; // child  -1     vtx
  using pr = pair<int,int>;
  int n, rt, k, num_node;
  V<V<pr>> g;
  V<int> PE, vh;
  struct Node { int p, l, r, e, t; };
  V<Node> A;
  StaticTopTree() {}
  StaticTopTree(int n, const V<pr>& tree, int root)
    : n(n)
    , rt(root)
    , k(0)
    , g(n)
    , PE(n, -1)
    , vh(n * 2, -1)
    , A(4 * n + 30, { -1, -1, -1, 0, -1 })
  {
    REP(i,n-1){
      auto [u,v] = tree[i];
      g[u].push_back({ v, i });
      g[v].push_back({ u, i });
    }
    dfs(rt);
    A.resize(num_node = comp(rt).first + 1);
  }
  int dfs(int c) {
    int s = 1, best = 0, t = 0;
    for (auto& e : g[c]) {
      auto [w, ei] = e;
      g[w].erase(ranges::find(g[w], pr{c, PE[w] = ei}));
      s += t = dfs(w);
      if (best < t) best = t, swap(e, g[c][0]);
    }
    return s;
  }
  int add(int l, int r, int e, int t) {
    A[k] = { -1, l, r, e, t };
    if (l >= 0) A[l].p = k;
    if (r >= 0) A[r].p = k;
    if (e >= 0) vh[e] = k;
    return k++;
  }
  pr merge(const V<pr>& a, int t) {
    if (a.size() == 1) return a[0];
    int u = 0;
    for (auto& [_, s] : a) u += s;
    V<pr> b, c;
    for (auto& [i, s] : a) {
      (u > s ? b : c).emplace_back(i, s);
      u -= s * 2;
    }
    int e = t == 1 ? n + PE[A[c[0].first].e] : -1;
    return {add(merge(b, t).first, merge(c, t).first, e, t), -u};
  }
  pr comp(int v) {
    V<pr> chs{addv(v)};
    while (g[v].size()) chs.push_back(addv(v = g[v][0].first));
    return merge(chs, 1);
  }
  pr rake(int v) {
    if(g[v].size() < 2) return {-1, 0};
    V<pr> chs;
    REP(i, g[v].size()-1) chs.push_back(adde(g[v][i + 1].first));
    return merge(chs, 2);
  }
  pr adde(int v) {
    auto [j, sj] = comp(v);
    return {add(j, -1, n + PE[v], 3), sj};
  }
  pr addv(int v) {
    auto [i, sj] = rake(v);
    return {add(i, -1, v, i < 0 ? 0 : 4), ++sj};
  }
  auto& operator[](int i) const { return A[i]; }
};
template<class Structure>
struct STTAgg {
  Structure d;
  V<class Structure::Node> A;
  StaticTopTree st;
  void agg(int v){
    auto [p,l,r,e,t] = st[v];
    if(t == 0) A[v].s = d.vert(e);
    if(t == 1) A[v].s = d.comp(A[l].s, e-st.n, A[r].s);
    if(t == 2) A[v].p = d.rake(A[l].p, A[r].p);
    if(t == 3) A[v].p = d.adde(e-st.n, A[l].s);
    if(t == 4) A[v].s = d.addv(e, A[l].p);
    if(t == 5) A[v].s = d.rev(A[l].s);
  }
  void aggX(int v){ while(v >= 0) agg(v), v = st[v].p; }
  void aggV(int v){ aggX(st.vh[v]); }
  void aggE(int e){ aggX(st.vh[st.n + e]); }
  void init(){
    A.resize(st.num_node);
    REP(i, A.size()) agg(i);
  }
};
struct STTStructure {
  struct Seg {};
  struct Pt {};
  struct Node {
    Seg s;
    Pt p;
  };
  Seg vert(int v){ return {}; }
  Seg comp(Seg l, int e, Seg r){ return {}; }
  Pt rake(Pt l, Pt r){ return {}; }
  Seg addv(int v, Pt p){ return {}; }
  Pt adde(int e, Seg s){ return {}; }
  Seg rev(Seg s){ return s; }
};
// V<pair<int,int>> edges(N-1);
// STTAgg<STTStructureInst> ds;
// ds.d.vtx = move(A);
// ds.d.edge = move(E);
// ds.st = StaticTopTree(N, edges, 0);
// ds.init();