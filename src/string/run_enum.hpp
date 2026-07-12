// itereator バージョンの z_algorithm が必要
struct Run { int p, l, r; }; // period, l, r
V<Run> EnumerateRuns(string S) {
  int n = S.size();
  V<Run> res;
  auto f = [&](auto& f, int l, int r) -> void {
    int len = r - l, lz = len / 2, rz = len - lz;
    if (len < 2) return;
    V<int> tg(len*2);
    REP(t,2) REP(i,len) tg[t*len + i] = S[l + i];
    f(f, l + lz, r);
    f(f, l, l + lz);
    auto a = z_algorithm(tg.begin() + lz, tg.end());
    auto b = z_algorithm(tg.rbegin() + rz, tg.rend());
    auto ch = [&](int p, int lx, int rx) {
      if (l != 0 && lx == lz) return;
      if (r != n && rx == rz) return;
      if (lx + rx < p * 2) return;
      res.push_back({ p, l + lz - lx, l + lz + rx });
    };
    for (int p = 1; p <= lz; p++) if (a[len - p] < p)
      ch(p, min(lz, b[p] + p), min(rz, a[len - p]));
    for (int p = 1; p <= rz; p++)
      ch(p, min(lz, b[len - p]), min(rz, a[p] + p));
  };
  f(f, 0, n);
  return res;
}