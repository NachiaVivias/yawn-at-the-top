#define PROBLEM "https://judge.yosupo.jp/problem/dominatortree"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;
#define REP(i,n) for(ll i=0; i<ll(n); i++)
template <class T> using V = vector<T>;

#include "src/graph/dominator_tree_gifted.hpp"


int main() {
    cin.tie(0)->sync_with_stdio(0);

    int N, M, s; cin >> N >> M >> s;
    auto dom = DominatorTree(N);
    for(int i=0; i<M; i++){
      int u,v; cin >> u >> v;
      dom.AddEdge(u, v);
    }
    auto par = dom.Calc(s);
    par[s] = s;
    for(int i=0; i<N; i++){
      if(i) cout << " ";
      cout << par[i];
    } cout << "\n";
}
