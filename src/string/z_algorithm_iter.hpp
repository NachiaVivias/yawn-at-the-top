template<class Iter>
V<int> z_algorithm(Iter s, Iter s_end) {
  int n = s_end - s;
  vector<int> r(n + 1);
  for (int i = 1, j = 0; i <= n; i++) {
    int& k = r[i];
    if (i < j + r[j]) k = min(j + r[j] - i, r[i - j]);
    while (i + k < n && s[k] == s[i + k]) k++;
    if (j + r[j] < i + r[i]) j = i;
  }
  r[0] = n;
  return r;
}