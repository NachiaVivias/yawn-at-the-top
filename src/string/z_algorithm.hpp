// s[0..r[i]] == s[i..i+r[i]]
template <class S>
vector<int> z_algorithm(const S& s) {
  int n = int(s.size());
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