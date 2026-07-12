// res[i] = ( l + r == i なる回文 s[l..r) の長さの最大値 )
// dummy は s 内で使用されていない値
template <class S>
V<int> manacher(const S& s, int dummy) {
  int n = s.size(), m = n * 2 + 1;
  S a(m, dummy);
  REP(i, n) a[i * 2 + 1] = s[i];
  V<int> r(m);
  r[0] = 1;
  for (int i = 1, j = 0; i < m; i++) {
    int& k = r[i];
    k = min(j + r[j] - i, r[2 * j - i]) * (i < j + r[j]);
    while (0 <= i - k && i + k < m && a[i - k] == a[i + k]) k++;
    if (j + r[j] < i + r[i]) j = i;
  }
  REP(i, m) r[i] -= 1;
  return r;
}