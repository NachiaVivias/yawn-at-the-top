/// Original: Nyaan https://nyaannyaan.github.io/library/game/surreal-number.hpp
/// edit: Nachia
struct Surreal {
  using S = Surreal;
  using Int = long long;
  Int p, q; // val = p / 2**q
  Surreal(Int p = 0, Int q = 0) : p(p), q(q) {
    while (p % 2 == 0 && q) p /= 2, q--;
  }
  S operator+(S r) const {
    auto c = max(q, r.q);
    return S((p << (c - q)) + (r.p << (c - r.q)), c);
  }
  S operator-() const { return {-p, q}; }
  bool operator<(S r) const { return (r + -*this).p > 0; }
  S lc() const {
    if (!q && p <= 0) return p - 1;
    return { p * 2 - 1, q + 1 };
  }
  friend S operator|(S l, S r) {
    assert(l < r);
    S v = 0;
    while (!(l < v && v < r))
      v = l < v ? v.lc() : -(-v).lc();
    return v;
  }
};