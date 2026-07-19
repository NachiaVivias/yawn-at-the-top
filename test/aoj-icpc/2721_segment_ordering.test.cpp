#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/challenges/sources/JAG/Summer/2721"

// maybe slows down std::stable_sort
// #define _GLIBCXX_DEBUG

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define REP(i,n) for(ll i=0; i<ll(n); i++)
template <class T> using V = vector<T>;


struct P {
  ll x, y;
};
P operator-(P l, P r){ return { l.x - r.x, l.y - r.y }; }
ll operator^(P l, P r){ return l.x * r.y - l.y * r.x; }
bool operator<(P l, P r){ return l.x != r.x ? l.x < r.x : l.y < r.y; }
ll sgn(ll x){ return x ? x < 0 ? -1 : 1 : 0; }

bool argcmp(P l, P r){
  if(r.y == 0 && 0 < r.x) return 0;
  if(l.y == 0 && 0 < l.x) return 1;
  ll sl = sgn(l.y), sr = sgn(r.y);
  if(sl != sr) return sl > sr;
  return (l ^ r) > 0;
}

ll dot(P a, P b) {
  return a.x * b.x + a.y * b.y;
}
ll sgncrs(P a, P b, P c){
  ll q = (b - a) ^ (c - a);
  return q ? q < 0 ? -1 : 1 : 0;
}

struct L {
  P s, t;
};

#include "src/geometry/segment_ordering.hpp"

void testcase(){
  struct Edge {
    ll ccw;
    ll cw;
    ll from;
    ll to;
  };
  
  ll N, M, Q; cin >> N >> M >> Q;
  V<P> A(N); REP(i,N) cin >> A[i].x >> A[i].y;
  V<V<ll>> adj(N);
  V<Edge> edges(M*2, {-1,-1,-1});
  auto edgeDir = [](P l, P r) -> bool {
    return l.y != r.y ? l.y < r.y : l.x < r.x;
  };
  {
    V<ll> I(N); REP(i,N) I[i] = i;
    sort(I.begin(), I.end(), [&](ll l, ll r){ return edgeDir(A[l], A[r]); });
    V<ll> O(N); REP(i,N) O[I[i]] = i;
    REP(i,M){
      ll u,v; cin >> u >> v; u--; v--; u = O[u]; v = O[v];
      adj[u].push_back(i*2);
      adj[v].push_back(i*2+1);
      edges[i*2].from = u;
      edges[i*2].to = v;
      edges[i*2+1].from = v;
      edges[i*2+1].to = u;
    }
    V<P> B(N);
    REP(i,N) B[i] = A[I[i]];
    swap(A, B);
  }
  REP(v,N) if(adj[v].size()){
    sort(adj[v].begin(), adj[v].end(), [&](ll l, ll r){
      ll f = edges[l].to, g = edges[r].to;
      return argcmp(A[f] - A[v], A[g] - A[v]);
    });
    REP(i,adj[v].size()){
      ll l = adj[v][i], r = adj[v][(i+1)%adj[v].size()];
      edges[l].ccw = r;
      edges[r].cw = l;
    }
  }

  V<ll> vis(M*2);
  V<ll> outer;
  REP(se,M*2) if(!vis[se]){
    ll area = 0;
    V<ll> echain;
    for(ll e = se; !vis[e]; e = edges[e^1].cw){
      area += A[edges[e].from] ^ A[edges[e].to];
      echain.push_back(e);
      vis[e] = 1;
    }
    if(area < 0) for(auto x : echain) outer.push_back(x);
  }

  sort(outer.begin(), outer.end());
  {
    V<ll> buf;
    for(ll x : outer){
      if(buf.size() && buf.back() == (x ^ 1)){
        buf.pop_back(); continue;
      }
      buf.push_back(x);
    }
    swap(outer, buf);
  }

  M = outer.size();

  V<P> pts(Q);
  for(auto& p : pts) cin >> p.x >> p.y;
  
  V<L> segs;
  for(auto e : outer) segs.push_back(L{ A[edges[e].from], A[edges[e].to] });
  REP(i,Q) segs.push_back(L{pts[i], pts[i]});
  auto ord = orderSegments(segs);

  struct Query {
    P pos;
    ll ty;
    ll e;
  };
  V<Query> queries;
  REP(i,Q) queries.push_back({ pts[i], 0, i });

  REP(i,M){
    ll u = edges[outer[i]].from;
    ll v = edges[outer[i]].to;
    queries.push_back({ min(A[u], A[v]), 1, i });
    queries.push_back({ max(A[u], A[v]), 2, i });
  }
  for(auto& q : queries) q.pos.y = q.pos.y * 3 + q.ty;
  sort(queries.begin(), queries.end(), [](auto& l, auto& r){ return l.pos < r.pos; });

  ll Z = M + Q;
  V<ll> fwt(Z+1);
  auto add = [&](ll p, ll v){
    p++;
    while(p <= Z){
      fwt[p] += v;
      p += p & -p;
    }
  };
  auto sum = [&](ll r){
    ll res = 0;
    while(r){
      res += fwt[r];
      r -= r & -r;
    }
    return res;
  };

  V<ll> ans(Q);
  for(auto query : queries){
    if(query.ty == 0){
      ans[query.e] = sum(ord[query.e + M]);
    }
    else {
      auto e = edges[outer[query.e]];
      bool way = A[e.from] < A[e.to];
      if(query.ty == 1){
        add(ord[query.e], way ? 1 : -1);
      }
      if(query.ty == 2){
        add(ord[query.e], way ? -1 : 1);
      }
    }
  }

  REP(i,Q) cout << (ans[i] ? "Yes\n" : "No\n");
}

int main(){
  cin.tie(0)->sync_with_stdio(0);
  testcase();
  return 0;
}