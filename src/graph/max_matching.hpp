/// Original: Gifted Infants(MaxMatching) https://yosupo.hatenablog.com/entry/2019/07/02/122433
// struct E { int to; };
template <class E> struct MaxMatching {
    int n;
    const V<V<E>>& g;
    V<int> mt; // mt[i] = i のマッチング相手
    V<int> is_ev, uf;
    V<pair<int,int>> nx;
    int st;
    int group(int x) {
        if (uf[x] == -1 || is_ev[uf[x]] != st) return uf[x];
        return uf[x] = group(uf[x]);
    }
    void match(int p, int b) {
        int d = mt[p];
        mt[p] = b;
        if (d == -1 || mt[d] != p) return;
        if (nx[p].second == -1) {
            mt[d] = nx[p].first;
            match(nx[p].first, d);
        } else {
            match(nx[p].first, nx[p].second);
            match(nx[p].second, nx[p].first);
        }
    }
    bool arg() {
        is_ev[st] = st;
        uf[st] = -1;
        nx[st] = { -1, -1 };
        V<int> q = {st};
        REP(qi, q.size()) {
            int a = q[qi];
            for (auto e : g[a]) {
                int b = e.to;
                if (b == st) continue;
                if (mt[b] == -1) {
                    mt[b] = a;
                    match(a, b);
                    return true;
                }
                if (is_ev[b] == st) {
                    int x = group(a), y = group(b);
                    if (x == y) continue;
                    int z = -1;
                    while (x != -1 || y != -1) {
                        if (y != -1) swap(x, y);
                        if (nx[x] == make_pair(a, b)) {
                            z = x;
                            break;
                        }
                        nx[x] = { a, b };
                        x = group(nx[mt[x]].first);
                    }
                    for (int v : {group(a), group(b)}) {
                        while (v != z) {
                            q.push_back(v);
                            is_ev[v] = st;
                            uf[v] = z;
                            v = group(nx[mt[v]].first);
                        }
                    }
                } else if (is_ev[mt[b]] != st) {
                    is_ev[mt[b]] = st;
                    nx[b] = { -1, -1 };
                    nx[mt[b]] = { a, -1 };
                    uf[mt[b]] = b;
                    q.push_back(mt[b]);
                }
            }
        }
        return false;
    }
    MaxMatching(const V<V<E>>& _g)
    : n(int(_g.size())), g(_g), mt(n, -1), is_ev(n, -1), uf(n), nx(n) {
        for(st = 0; st < n; st++) if (mt[st] == -1) arg();
    }
};
