/// BEGIN https://github.com/NachiaVivias/yawn-at-the-top/blob/main/src/fps/taylor_shift.hpp
// f(x+c)を返す
template<class Mint>
V<Mint> taylor_shift(V<Mint> a, Mint c) {
  int n = a.size();
  V<Mint> b(n + 1, 1), fi(n);
  Mint f = 1;
  REP(i, n) {
    a[i] *= f;
    f *= i + 1;
    b[i + 1] = b[i] * c;
  }
  f = f.inv();
  REP(i, n) b[n - 1 - i] *= fi[n - 1 - i] = f *= n - i;
  reverse(b.begin(), b.end());
  a = multiply(a, b);
  REP(i, n) fi[i] *= a[i + n];
  return fi;
}
/// END https://github.com/NachiaVivias/yawn-at-the-top/blob/main/src/fps/taylor_shift.hpp
