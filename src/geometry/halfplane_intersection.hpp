/// Original: Gifted Infants(複雑系) https://yosupo.hatenablog.com/entry/2019/07/02/122433
int argcmp(P l, P r) {
    auto psgn = [&](P p) {
        if (int u = sgn(p.y)) return u;
        if (sgn(p.x) == -1) return 2;
        return 0;
    };
    int lsgn = psgn(l), rsgn = psgn(r);
    if (lsgn < rsgn) return -1;
    if (lsgn > rsgn) return 1;
    return sgncrs(r, l);
}
// line = (s,t) としたとき、 s-->t の方向に見たときの右側を切り捨てる
V<L> halfplane_intersection(V<L> lines) {
    auto st = move(lines);
    sort(st.begin(), st.end(), [](L a, L b) {
        if (int u = argcmp(a.vec(), b.vec())) return u == -1;
        return sgncrs(a.vec(), b.s - a.s) < 0;
    });
    st.erase(unique(st.begin(), st.end(), [](L a, L b) { return !argcmp(a.vec(), b.vec()); }), st.end());
    ll l = 0, r = -1, err = 0;
    for (auto& g : st) {
        auto need = [&](L a, L b, L c) {
            D ab_dw = crs(a.vec(), b.vec()), ab_up = crs(a.vec(), a.t - b.s);
            D bc_dw = crs(b.vec(), c.vec()), bc_up = crs(c.t - b.s, c.vec());
            if (ab_dw <= 0 || bc_dw <= 0) return true;
            bool f = bc_up * ab_dw > bc_dw * ab_up;
            if (!f && crs(a.vec(), c.vec()) < 0) err = 1;
            return f;
        };
        while (r - l >= 1 && !need(g, st[l], st[l + 1])) l++;
        while (r - l >= 1 && !need(st[r - 1], st[r], g)) r--;
        if (r - l < 1 || need(st[r], g, st[l])) st[++r] = g;
        if (err) return {};
    }
    if (r - l == 1 && !sgncrs(st[l].vec(), st[r].vec()) &&
        sgncrs(st[l].vec(), st[r].s - st[l].s) <= 0)
        return {};
    return V<L>(st.begin() + l, st.begin() + r + 1);
}