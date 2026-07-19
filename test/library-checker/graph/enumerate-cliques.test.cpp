#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_cliques"

#define _GLIBCXX_DEBUG

#include <bits/stdc++.h>
using namespace std;
template <class T> using V = vector<T>;
using ll = long long;
#define REP(i,n) for(ll i=0; i<ll(n); i++)

#include "src/graph/cliques.hpp"
#include "src/number-theory/modint.hpp"


using Mint = ModInt<998244353, 3>;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  
  int N, M; cin >> N >> M;
  
  vector<Mint> A(N);
  for(int i=0; i<N; i++){ int a; cin >> a; A[i] = a; }
  
  vector<vector<int>> graph(N);
  for(int i=0; i<M; i++){
    int u,v; cin >> u >> v;
    graph[u].push_back(v);
    graph[v].push_back(u);
  }

  Mint ans = 0;
  cliques(N, graph, [&](auto& C){
    Mint x = 1;
    for(auto v : C) x *= A[v];
    ans += x;
  });

  cout << ans.v << "\n";
  
  return 0;
}
