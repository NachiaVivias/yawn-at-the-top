/// 資料: https://noshi91.hatenablog.com/entry/2023/02/18/005856
// Int f(int a, int b){ return A[a][b] } (A : monge)
// void det(int i, int j, Int x){
//     argmin[i] = j; mimval[i] = x; }
template <class Int, class F1, class F2>
void easy_larsch(int n, F1 f, F2 det, Int inf){
  V<int> a(n, 0);
  V<Int> b(n, inf);
  n--;
  auto check = [&](int i, int k, int d){
    Int v = f(i,k);
    if(v < b[i]) a[i] = k, b[i] = v;
  };
  auto dfs = [&](auto& dfs, int l, int r, int d) -> void {
      if (r - l == 1) return (void) det(r, a[r], b[r]);
      int m = (l + r) / 2;
      for (int k = a[l]; k <= a[r]; k++) check(m, k, d);
      dfs(dfs, l, m, d + 1);
      for (int k = l + 1; k <= m; k++) check(r, k, d);
      dfs(dfs, m, r, d + 1);
  };
  check(n, 0, 0);
  dfs(dfs, 0, n, 1);
}
// Int f(int a, int b){ return dist(a,b) } (dist : monge)
template <class Int, class F1>
Int d_edge_shortest_path(int n, ll k, F1 f, Int max_weight, Int INF) {
  Int inf = max_weight;  // 辺の重みより大きい値
  auto DC = [&](Int p) -> pair<Int, ll> {
    vector<Int> D(n, INF);
    vector<int> P(n);
    D[0] = 0;
    easy_larsch(n,
      [&](int a, int b){ return D[b] + f(b, a) - p; },
      [&](int a, int b, Int c){ P[a] = b, D[a] = c; },
      INF);
    ll c = 0, v = n-1;
    for(; v; v = P[v]) c++;
    return { D[n - 1], c };
  };
  Int m = -inf + 1;  // 辺の重みが正なら0にしてもいい
  Int ok = m, ng = inf;
  while (abs(ok - ng) > 1) {
    auto mid = (ok + ng) / 2;
    auto [d, c] = DC(mid);
    (c <= k ? ok : ng) = mid;
  }
  if (ok == m) return -INF;
  auto [d, c] = DC(ok);
  return d + ok * k;
}