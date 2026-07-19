#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/6/GRL_6_B"

// maybe slows down std::priority_queue
// #define _GLIBCXX_DEBUG

#include "src/common/template.hpp"
#include "src/graph/min_cost_flow.hpp"

int main() {
    int n, m, f; cin >> n >> m >> f;
    MCF mcf(n);
    struct E {
      int to, rev, cap, dist;
    };
    vector<vector<E>> g;
    auto add_edge = [&](int from, int to, int cap, int dist) {
      mcf.addEdge(from, to, cap, dist);
    };
    g.resize(n);
    for(int i = 0; i < m; i++) {
        int u, v, c, d; cin >> u >> v >> c >> d;
        add_edge(u, v, c, d);
    }
    auto res = mcf.flow(0, n-1, f);
    if(res.first < f) cout << -1 << '\n';
    else cout << res.second << '\n';
}

