template <int MD, int g = 3>
struct ModInt {
  using M = ModInt;
  const static inline M G = g;
  unsigned int v;
  ModInt() : v(0) {}
  ModInt(ll w) : v(w % MD + MD) {
    if(v >= MD) v -= MD;
  }
  static M raw(unsigned int v) {
    M res;
    res.v = (v < MD) ? v : v - MD;
    return res;
  }
  explicit operator bool() const {
    return v != 0;
  }
  M operator-() const {
    return M() - *this;
  }
  M operator+(M r) const {
    return raw(v + r.v);
  }
  M operator-(M r) const {
    return raw(v + MD - r.v);
  }
  M operator*(M r) const {
    return raw(ll(v) * r.v % MD);
  }
  M operator/(M r) const {
    return *this * r.inv();
  }
  M& operator+=(M r) {
    return *this = *this + r;
  }
  M& operator-=(M r) {
    return *this = *this - r;
  }
  M& operator*=(M r) {
    return *this = *this * r;
  }
  M& operator/=(M r) {
    return *this = *this / r;
  }
  bool operator==(M r) const {
    return v == r.v;
  }
  M pow(ll n) const {
    M x = *this, r = 1;
    while (n) {
      if (n & 1) r *= x;
      x *= x;
      n >>= 1;
    }
    return r;
  }
  M inv() const {
    return pow(MD - 2);
  }
  friend ostream& operator<<(ostream& os, M r) {
    return os << r.v;
  }
};
// using Mint = ModInt<998244353, 3>;
