template <class D>
struct Poly {
  using P = const Poly&;
  V<D> v;
  Poly(V<D> v = {}) : v(move(v)) {}
  void shrink() {
    while (v.size() && !v.back()) v.pop_back();
  }
  int size() const {
    return v.size();
  }
  D freq(int p) const {
    return 0 <= p && p < size() ? v[p] : D(0);
  }
  Poly operator+(P r) const {
    V<D> res(max(size(), r.size()));
    REP(i, res.size()) res[i] = freq(i) + r.freq(i);
    return res;
  }
  Poly operator-(P r) const {
    V<D> res(max(size(), r.size()));
    REP(i, res.size()) res[i] = freq(i) - r.freq(i);
    return res;
  }
  Poly operator*(P r) const {
    return {multiply(v, r.v)};
  }
  Poly operator*(D r) const {
    V<D> res = v;
    REP(i, size()) res[i] *= r;
    return res;
  }
  Poly operator/(D r) const {
    return *this * r.inv();
  }
  Poly operator/(Poly r) const {
    if (size() < r.size()) return {{}};
    r.shrink();
    int n = size() - r.size() + 1;
    return (rev().pre(n) * r.rev().inv(n)).rev(n);  // 変更
  }
  Poly operator%(P r) const {
    auto x = *this - *this / r * r;
    x.shrink();
    return x;
  }
  Poly& operator+=(P r) {
    return *this = *this + r;
  }
  Poly& operator-=(P r) {
    return *this = *this - r;
  }
  Poly& operator*=(P r) {
    return *this = *this * r;
  }
  Poly& operator*=(D r) {
    return *this = *this * r;
  }
  Poly& operator/=(P r) {
    return *this = *this / r;
  }
  Poly& operator/=(D r) {
    return *this = *this / r;
  }
  Poly& operator%=(P r) {
    return *this = *this % r;
  }
  Poly clip(int l = 0, int r = -(1 << 30)) const {
    if(r == -(1 << 30)) r = size();
    if(r < l) r = l;
    V<D> res(r - l);
    REP(i, r - l) res[i] = freq(i + l);
    return res;
  }
  Poly pre(int le) const {
    return clip(0, le);
  }
  Poly rev(int n = -1) const {
    auto res = v;
    if (n != -1) res.resize(n);
    reverse(res.begin(), res.end());
    return res;
  }
  Poly diff() const {
    auto res = clip(1).v;
    REP(i,res.size()) res[i] *= i + 1;
    return res;
  }
  Poly inte() const {
    auto res = clip(-1).v;
    REP(i,res.size()) if(i) res[i] /= i;
    return res;
  }
  // f * f.inv() = 1 + g(x)x^m
  Poly inv(int m) const {
    Poly f = Poly({D(1) / freq(0)});
    for (int i = 1; i < m; i *= 2)
      f = (f * D(2) - f * f * pre(2 * i)).pre(2 * i);
    return f.pre(m);
  }
  Poly exp(int n) const {
    assert(freq(0) == 0);
    Poly f({1}), g({1}), q;
    for (int i = 2; i < n * 2; i *= 2) {
      g = (g * 2 - f * g * g).pre(i / 2);
      q = pre(i / 2).diff();
      q += (g * (f.diff() - f * q)).pre(i - 1);
      f += (f * (pre(i) - q.inte())).pre(i);
    }
    return f.pre(n);
  }
  Poly log(int n) const {
    assert(freq(0) == 1);
    auto f = pre(n);
    return (f.diff() * f.inv(n - 1)).pre(n - 1).inte();
  }
  friend ostream& operator<<(ostream& os, P p) {
    if (p.size() == 0) return os << "0";
    for (auto i = 0; i < p.size(); i++) {
      if (p.v[i]) {
        os << p.v[i] << "x^" << i;
        if (i != p.size() - 1) os << "+";
      }
    }
    return os;
  }
};