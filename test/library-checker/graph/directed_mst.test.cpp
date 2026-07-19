#define PROBLEM "https://judge.yosupo.jp/problem/directedmst"

#define _GLIBCXX_DEBUG

#include "src/common/template.hpp"

#include "src/graph/directed_mst.hpp"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, m, r;
  cin >> n >> m >> r;
  vector<Edge> edges;
  for(int i = 0; i < m; ++i) {
    int a, b;
    int64_t w;
    cin >> a >> b >> w;
    edges.emplace_back(a, b, w);
  }
  auto ans = directed_mst(n, r, edges);
  ll cost = 0;
  for(auto &e : ans) if(e != -1){
    cost += edges[e].cost;
    e = edges[e].from;
  }
  ans[r] = r;
  cout << cost << "\n";
  for(int i = 0; i < n; ++i) {
    if(i) cout << " ";
    cout << ans[i];
  } cout << "\n";
}