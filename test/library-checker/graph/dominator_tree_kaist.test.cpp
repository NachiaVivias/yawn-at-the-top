#define PROBLEM "https://judge.yosupo.jp/problem/dominatortree"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;
#define REP(i,n) for(ll i=0; i<ll(n); i++)
template <class T> using V = vector<T>;
template<class A, class B>
bool chmax(A &a, B b) { return a < b && (a = b, true); }
template<class A, class B>
bool chmin(A &a, B b) { return b < a && (a = b, true); }

#include "src/graph/dominator_tree_kaist.hpp"


int main() {
    cin.tie(0)->sync_with_stdio(0);

    int N, M, s; cin >> N >> M >> s;
    auto dom = DominatorTree(N);
    for(int i=0; i<M; i++){
      int u,v; cin >> u >> v;
      dom.add_edge(u, v);
    }
    auto par = dom.solve(s);
    par[s] = s;
    for(int i=0; i<N; i++){
      if(i) cout << " ";
      cout << par[i];
    } cout << "\n";
}
