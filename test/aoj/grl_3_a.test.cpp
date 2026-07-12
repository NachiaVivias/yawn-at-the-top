#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/3/GRL_3_A"

#include "src/common/template.hpp"
#include "src/graph/biconnectivity.hpp"

int main() {
    int v, e; cin >> v >> e;
    vector g(v, vector<int>());
    for(int _ : views::iota(0, e)) {
        int s, t; cin >> s >> t;
        g[s].push_back(t);
        g[t].push_back(s);
    }
    Biconnectivity bc(v, g);
    vector<int> deg(v), ans;
    for(auto [a,b] : bc.bct) deg[b] += 1;
    for(int i=0; i<v; i++) if(deg[i] >= 2) cout << i << "\n";

    return 0;
}
