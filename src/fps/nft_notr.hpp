/// Original: tatyam (ICPC_notebook) (https://github.com/tatyam-prime/ICPC_notebook/tree/main)
// 167772161     3       5 * 2^25 + 1
// 377487361     7      45 * 2^23 + 1
// 469762049     3       7 * 2^26 + 1
// 595591169     3      71 * 2^23 + 1
// 645922817     3      77 * 2^23 + 1
// 754974721    11      45 * 2^24 + 1
// 880803841    26     105 * 2^23 + 1
// 897581057     3     107 * 2^23 + 1
// 998244353     3     119 * 2^23 + 1
template <class Mint>
void nft(bool type, V<Mint>& a) {
  int n = int(a.size()), s = 0;
  while ((1 << s) < n) s++;
  assert(1 << s == n);
  static V<Mint> ep;
  while (int(ep.size()) <= s) {
    ep.push_back(Mint::G.pow(Mint(-1).v >> ep.size()));
  }
  V<Mint> b(n);
  REP(i, s) {
    int w = 1 << (s - i - 1);
    Mint now = 1;
    for (int y = 0; y < n / 2; y += w) {
      REP(x, w) {
        auto l = a[y << 1 | x];
        auto r = now * a[y << 1 | x | w];
        b[y | x] = l + r;
        b[y | x | n >> 1] = l - r;
      }
      now *= ep[i + 1];
    }
    swap(a, b);
  }
  if(type) reverse(a.begin() + 1, a.end());
}
template <class Mint>
V<Mint> multiply(V<Mint> a, V<Mint> b) {
  int n = int(a.size()), m = int(b.size());
  if (!n || !m) return {};
  if (min(n, m) <= 32) {
    V<Mint> ans(n + m - 1);
    REP(i, n) REP(j, m) ans[i + j] += a[i] * b[j];
    return ans;
  }
  int z = 1;
  while (z < n + m - 1) z *= 2;
  a.resize(z);
  b.resize(z);
  nft(0, a);
  nft(0, b);
  REP(i, z) a[i] *= b[i];
  nft(1, a);
  a.resize(n + m - 1);
  Mint iz = Mint(z).inv();
  for(auto& x : a) x *= iz;
  return a;
}