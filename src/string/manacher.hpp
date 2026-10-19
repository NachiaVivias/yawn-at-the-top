/// BEGIN https://github.com/NachiaVivias/yawn-at-the-top/blob/main/src/string/manacher.hpp
// res[i] = ( l + r == i なる回文 s[l..r) の長さの最大値 )
template <class S>
V<int> manacher(const S& s) {
  if(s.empty()) return {0};
  int n = s.size(), m = n * 2 + 1;
  S a(m, s[0]);
  REP(i, n) a[i * 2 + 1] = s[i];
  V<int> r(m, 1);
  for (int i = 1, j = 0; i < m; i++) {
    int& k = r[i];
    k = i < j + r[j] ? min(j + r[j] - i, r[2 * j - i]) : 0;
    while (0 <= i - k && i + k < m && a[i - k] == a[i + k]) k++;
    if (j + r[j] < i + r[i]) j = i;
  }
  REP(i, m) r[i]--;
  return r;
}
/// END https://github.com/NachiaVivias/yawn-at-the-top/blob/main/src/string/manacher.hpp
