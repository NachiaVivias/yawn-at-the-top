/// Original: Nyaan's Library https://nyaannyaan.github.io/library/fps/berlekamp-massey.hpp
// 有理母関数の分母を返す
template <class Mint>
vector<Mint> berlekamp_massey(const vector<Mint>& s) {
  int n = int(s.size());
  vector<Mint> b = {1}, c = {1}, t;
  Mint y = 1;
  REP(ed, n){
    int l = c.size(), m = b.size() + 1;
    Mint x = 0;
    REP(i,l) x -= c[i] * s[ed - i];
    b.insert(begin(b), 0);
    if (!x.v) continue;
    Mint q = x / y;
    if (l < m) t = c, c.resize(m, 0);
    REP(i, m) c[i] -= q * b[i];
    if (l < m) b = t, y = x;
  }
  return c;
}