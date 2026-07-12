struct RollingHash {
  using ull = unsigned long long;
  constexpr static ull MOD = (1ULL << 61) - 1;
  // a < MOD, b < MOD必須
  constexpr static ull add(ull a, ull b) {
    if ((a += b) >= MOD) a -= MOD;
    return a;
  }
  // a < MOD, b < MOD必須
  constexpr static ull mul(ull a, ull b) {
    __uint128_t c = (__uint128_t)(a)*b;
    return add((ull)(c >> 61), (ull)(c & MOD));
  }
  void expand(int n) {
    while (int(power.size()) <= n)
      power.push_back(mul(power.back(), base));
  }

  unsigned base;
  vector<ull> power;
  RollingHash() {
    base = random_device{}();
    power = {1};
  }
  vector<ull> build(const auto& s) {
    vector<ull> res;
    res.reserve(ssize(s) + 1);
    res.push_back(0);
    for (auto c : s) {
      res.push_back(add(mul(res.back(), base), c));
    }
    return res;
  }
  ull query(const vector<ull>& hash, int l, int r) {
    expand(r - l);
    return add(hash[r], MOD - mul(hash[l], power[r - l]));
  }
};
