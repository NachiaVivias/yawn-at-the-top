#define PROBLEM "https://judge.yosupo.jp/problem/suffixarray"

#define _GLIBCXX_DEBUG

#include <bits/stdc++.h>
using namespace std;
template <class T> using V = vector<T>;
using ll = long long;
#define REP(i,n) for(ll i=0; i<ll(n); i++)


#include "src/string/suffix_automaton.hpp"



V<int> suffix_array_from_suffix_automaton(string s) {
  int n = s.size();
  SuffixAutomaton sa(s.size());
  for(char c : s) sa.add_char(c);
  sa.TopologicalSort();
  V<int> ans(n), L(sa.sz, -1), R(sa.sz), reach_depth(sa.sz), isEnd(sa.sz);
  for(auto p = sa.last; p; p = p->link) isEnd[p->id] = 1;
  int pt = 0;
  auto dfs = [&](auto& dfs, int v, int dep) -> void {
    if(L[v] == -1){
      reach_depth[v] = dep;
      L[v] = pt;
      if(dep > 0 && isEnd[v]) ans[pt++] = n - dep;
      for(auto [ch, w] : sa.nodes[v]->next){
        if(v >= w->id) exit(1); // Topological sort test
        dfs(dfs, w->id, dep + 1);
      }
      R[v] = pt;
    } else {
      for(int i=L[v]; i<R[v]; i++){
        ans[pt++] = ans[i] + reach_depth[v] - dep;
      }
    }
  };
  dfs(dfs, 0, 0);
  return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    
    string s; cin >> s;
    auto ans = suffix_array_from_suffix_automaton(s);
    for(int i=0; i<int(s.size()); i++){
        if(i) cout << " ";
        cout << ans[i];
    } cout << "\n";

    return 0;
}
