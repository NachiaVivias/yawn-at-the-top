#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/6/GRL_6_A"

#include <bits/stdc++.h>
using namespace std;

template <typename T>
using V = vector<T>;

#include "src/graph/max_flow.hpp"

int main() {
  int v, e;
  cin >> v >> e;
  struct E {
    int to, rev, cap;
  };
  vector<vector<E>> g(v);
  auto add_edge = [&](int from, int to, int cap) {
    g[from].push_back(E{to, int(g[to].size()), cap});
    g[to].push_back(E{from, int(g[from].size()) - 1, 0});
  };
  for (int i = 0; i < e; i++) {
    int u, v, c;
    cin >> u >> v >> c;
    add_edge(u, v, c);
  }
  auto mf = get_mf(g, 0, v - 1, 0);
  cout << mf.flow << endl;
}
