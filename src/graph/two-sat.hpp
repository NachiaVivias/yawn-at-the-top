/// Original: DaiMonge https://github.com/tko919/ICPC_notebook/blob/main/src/graph/twosat.hpp
struct TwoSat {
    int n;
    V<bool> res;
    V<V<int>> g;
    TwoSat(int n) : n(n), g(n * 2) {}
    void add(int x) { g.resize((n += x) * 2); }
    void either(ll i, bool fi, ll j, bool fj) {
        i = i * 2 + fi, j = j * 2 + fj;
        g[i ^ 1].push_back(j);
        g[j ^ 1].push_back(i);
    }
    bool solve() {
        auto id = scc(g.size(), g).second;
        res.resize(n);
        REP(i,n) if(id[i*2] == id[i*2+1]) return 0;
        REP(i,n) res[i] = id[i*2] < id[i*2+1];
        return 1;
    }
    void atMostOne(V<pair<ll, bool>> a) {
        ll x = n, i = 0;
        add(a.size());
        for(auto [v, f] : a){
            either(v, !f, x + i, 1);
            if(i) either(x + i - 1, 0, x + i, 1);
            if(i) either(v, !f, x + i - 1, 0);
            i++;
        }
    }
};
