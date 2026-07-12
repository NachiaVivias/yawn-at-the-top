/// Original: DeobureoMinkyuParty https://github.com/koosaga/DeobureoMinkyuParty
struct DominatorTree{
    int n, cs;
    V<V<int>> E, RE, rdom;
    V<int> S, RS, par, val, sdom, rp, idom;
    DominatorTree(int n):
        n(n), cs(0), E(n), RE(n), rdom(n)
    {
        S = RS = par = val = sdom = rp = idom = V<int>(n, -1);
    }
    void add_edge(int x, int y) { E[x].push_back(y); }
    int find(int x, int c = 0) {
        if(par[x] == x) return c ? -1 : x;
        int &w = par[x], p = find(w, 1);
        if(p < 0) return c ? w : val[x];
        if(sdom[val[x]] > sdom[val[w]]) val[x] = val[w];
        w = p;
        return c ? p : val[x];
    }
    void dfs(int x) {
        par[cs] = sdom[cs] = val[cs] = cs;
        RS[ S[x] = cs++ ] = x;
        for(int e : E[x]) {
            if(S[e] < 0) dfs(e), rp[S[e]] = S[x];
            RE[S[e]].push_back(S[x]);
        }
    }
    V<int> solve(int src) { // idom[v] : dom tree で v の親
        dfs(src);
        for (int i = cs - 1; i >= 0; i--) {
            for (int e : RE[i]) chmin(sdom[i], sdom[find(e)]);
            if (i) rdom[sdom[i]].push_back(i);
            for (int e : rdom[i]) {
                int p = find(e);
                idom[RS[e]] = RS[sdom[p] == i ? i : p];
            }
            if (i) par[i] = rp[i];
        }
        REP(i, cs)
            if(i && RS[sdom[i]] != idom[RS[i]])
                idom[RS[i]] = idom[idom[RS[i]]];
        return idom;
    }
};