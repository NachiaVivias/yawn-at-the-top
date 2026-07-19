#define PROBLEM "https://judge.yosupo.jp/problem/bipartitematching"

#define _GLIBCXX_DEBUG

#include <bits/stdc++.h>
using namespace std;
template <class T>
using V = vector<T>;

#include "src/graph/max_flow.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    
    int l, r, m; cin >> l >> r >> m;
    struct E {
      int to, rev, cap;
    };
    vector<vector<E>> g(l+r+2);
    auto add_edge = [&](int from, int to, int cap) {
      g[from].push_back(E{to, int(g[to].size()), cap});
      g[to].push_back(E{from, int(g[from].size())-1, 0});
    };
    for(int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        add_edge(a, l+b, 1);
    }
    for(int i = 0; i < l; i++) {
        add_edge(l+r, i, 1);
    }
    for(int i = 0; i < r; i++) {
        add_edge(l+i, l+r+1, 1);
    }
    auto f = get_mf(g, l+r, l+r+1, 0).flow;
    cout << f << '\n';
    for(int i = 0; i < l; i++) {
        for(auto&& e : g[i]) {
            if(e.to < l+r && e.cap == 0) {
                cout << i << ' ' << e.to-l << '\n';
                f--;
            }
        }
    }
    assert(f == 0);
}
