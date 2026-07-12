Mint Hook_Length_Formula(vector<int>& A) {
  assert(is_sorted(A.begin(), A.end()));
  if (A.empty()) return Mint(1);
  vector<int> L(A.back(), 0);
  Mint n(1), d(1);
  int s = 0;
  for (int l : A) REP(j, l) {
    n *= Mint(++s);
    d *= Mint(L[j]++ + l - j);
  }
  return n / d;
}