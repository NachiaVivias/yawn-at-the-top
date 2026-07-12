/// Original: DaiMonge https://github.com/tko919/ICPC_notebook/blob/main/src/graph/general.hpp
V<pair<ll, ll>> MaxMatching(ll n, V<pair<ll, ll>> &es){
    mt19937 rnd;
    V<V<ll>> g(n + 1);
    for(auto &[u, v] : es) {
        g[u + 1].push_back(v + 1);
        g[v + 1].push_back(u + 1);
    }
    V<ll> used(n + 1), mate(n + 1);
    ll T;
    auto dfs = [&](auto &dfs, ll v) -> bool {
        used[v] = T;
        shuffle(g[v].begin(), g[v].end(), rnd);
        for(auto &u : g[v]){
            ll w = mate[u];
            if(used[w] < T){
                mate[v] = u, mate[u] = v, mate[w] = 0;
                if (!w or dfs(dfs, w)) return 1;
                mate[u] = w, mate[w] = u, mate[v] = 0;
            }
        }
        return 0;
    };
    REP(_, 10){
        used.assign(n + 1, 0);
        REP(v, n) if(!mate[v + 1]) T++, dfs(dfs, v + 1);
    }
    V<pair<ll, ll>> ret;
    REP(v, n) if(v + 1 < mate[v + 1]) ret.push_back({v, mate[v + 1] - 1});
    return ret;
}