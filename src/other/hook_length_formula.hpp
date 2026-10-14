/// BEGIN https://github.com/NachiaVivias/yawn-at-the-top/blob/main/src/other/hook_length_formula.hpp
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
/// END https://github.com/NachiaVivias/yawn-at-the-top/blob/main/src/other/hook_length_formula.hpp
