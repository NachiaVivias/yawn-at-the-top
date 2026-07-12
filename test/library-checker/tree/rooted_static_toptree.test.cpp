#define PROBLEM "https://judge.yosupo.jp/problem/point_set_tree_path_composite_sum_fixed_root"

#include "src/common/template.hpp"
#include "src/tree/static_top_tree.hpp"


template <int MD, int g = 3>
struct ModInt {
  using M = ModInt;
  const static inline M G = g;
  unsigned int v;
  ModInt() : v(0) {}
  ModInt(ll w) : v(w % MD + MD) {
    if(v >= MD) v -= MD;
  }
  static M raw(unsigned int v) {
    M res;
    res.v = (v < MD) ? v : v - MD;
    return res;
  }
  explicit operator bool() const {
    return v != 0;
  }
  M operator-() const {
    return M() - *this;
  }
  M operator+(M r) const {
    return raw(v + r.v);
  }
  M operator-(M r) const {
    return raw(v + MD - r.v);
  }
  M operator*(M r) const {
    return raw(ll(v) * r.v % MD);
  }
  M operator/(M r) const {
    return *this * r.inv();
  }
  M& operator+=(M r) {
    return *this = *this + r;
  }
  M& operator-=(M r) {
    return *this = *this - r;
  }
  M& operator*=(M r) {
    return *this = *this * r;
  }
  M& operator/=(M r) {
    return *this = *this / r;
  }
  bool operator==(M r) const {
    return v == r.v;
  }
  M pow(long long n) const {
    M x = *this, r = 1;
    while (n) {
      if (n & 1) r *= x;
      x *= x;
      n >>= 1;
    }
    return r;
  }
  M inv() const {
    return pow(MD - 2);
  }
  friend ostream& operator<<(ostream& os, M r) {
    return os << r.v;
  }
};

using Mint = ModInt<998244353>;

struct Affine { Mint a, b; };
Affine operator*(Affine l, Affine r){
  return { l.a * r.a, l.a * r.b + l.b };
}
struct Weight { Mint c, z; };
Weight operator+(Weight l, Weight r){
  return { l.c + r.c, l.z + r.z };
}
Weight operator*(Affine l, Weight r){
  return { r.c, l.a * r.z + l.b * r.c };
}


struct STTStructureInst {
  struct Seg {
    Affine uv;
    Weight wt;
  };
  struct Pt {
    Weight wt;
  };
  struct Node {
    Seg s;
    Pt p;
  };
  vector<Mint> vtx;
  vector<Affine> edge;
  Seg vert(int v){ return { { 1, 0 }, { 1, vtx[v] } }; }
  Seg comp(Seg l, int e, Seg r){
    return { l.uv * edge[e] * r.uv, l.wt + l.uv * edge[e] * r.wt };
  }
  Pt rake(Pt l, Pt r){
    return { l.wt + r.wt };
  }
  Seg addv(int v, Pt p){
    return { { 1, 0 }, vert(v).wt + p.wt };
  }
  Pt adde(int e, Seg s){
    return { edge[e] * s.wt };
  }
  Seg rev(Seg s){ return s; }
};

int main(){
  cin.tie(0)->sync_with_stdio(0);
    
  int N; cin >> N;
  int Q; cin >> Q;

  vector<Mint> A(N);
  for(auto& a : A){ int v; cin >> v; a = v; }
  vector<pair<int,int>> edges(N-1);
  vector<Affine> E(N-1);
  for(int i=0; i<N-1; i++){
    int u,v,b,c; cin >> u >> v >> b >> c;
    edges[i] = {u,v};
    E[i] = {b,c};
  }

  STTAgg<STTStructureInst> ds;
  ds.d.vtx = move(A);
  ds.d.edge = move(E);
  ds.st = StaticTopTree(N, edges, 0);
  ds.init();

  for(int qi=0; qi<Q; qi++){
    int t; cin >> t;
    if(t == 0){
      int w, z; cin >> w >> z;
      ds.d.vtx[w] = z;
      ds.aggV(w);
    } else {
      int e, y, z; cin >> e >> y >> z;
      ds.d.edge[e] = { y,z };
      ds.aggE(e);
    }

    cout << ds.A.back().s.wt.z.v << "\n";
  }
  return 0;
}
