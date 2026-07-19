#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/3/GRL_3_B"

#define _GLIBCXX_DEBUG

#include "src/common/template.hpp"
#include "src/graph/biconnectivity.hpp"

int main() {
    int v, e; cin >> v >> e;
    vector g(v, vector<int>());
    vector<pair<int, int>> edges;
    for(int _ : views::iota(0, e)) {
        int s, t; cin >> s >> t;
        g[s].push_back(t);
        g[t].push_back(s);
        edges.push_back({s, t});
    }
    for(auto& [s, t] : edges) if(s > t) swap(s, t);
    ranges::sort(edges);

    Biconnectivity bc(v, g);
    for(auto [a, b] : edges) if(bc.tecc[a] != bc.tecc[b]) cout << a << " " << b << "\n";

    return 0;
}
