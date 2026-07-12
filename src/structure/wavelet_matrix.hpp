struct BitVector {
  ll n, b, m;
  V<unsigned> bit, sum;

  BitVector(ll n = 0) : n(n), b(n / 32 + 1), bit(b), sum(b + 1) {}
  void build() {
    REP(i, b) sum[i + 1] = sum[i] + popcount(bit[i]);
    m = n - sum[b];
  }
  int rank(int k) {
    return sum[k >> 5] +
           popcount(bit[k >> 5] & ~(~0u << (k & 31)));
  }
  int rank(bool val, int k) {
    return val ? rank(k) : k - rank(k);
  }
};

template <typename T, int MAXLOG>
struct WaveletMatrix {
  size_t n;
  BitVector a[MAXLOG];
  WaveletMatrix(V<T> v = {}) : n(v.size()) {
    V<T> l(n), r(n);
    for (int d = MAXLOG - 1; d >= 0; d--) {
      a[d] = BitVector(n);
      int x = 0, y = 0;
      REP(i, n) {
        unsigned h = (v[i] >> d) & 1;
        a[d].bit[i >> 5] |= h << (i & 31);
        (h ? r[y++] : l[x++]) = v[i];
      }
      a[d].build();
      v.swap(l);
      REP(i, y) v[x + i] = r[i];
    }
  }
  pair<int, int> succ(bool f, int l, int r, int d) {
    return {a[d].rank(f, l) + a[d].m * f,
            a[d].rank(f, r) + a[d].m * f};
  }
  // count i s.t. (0 <= i < r) && v[i] == x
  int rank(const T &x, int r) {
    int l = 0;
    for (int d = MAXLOG - 1; d >= 0; d--) {
      tie(l, r) = succ((x >> d) & 1, l, r, d);
    }
    return r - l;
  }
  // k-th(0-indexed) smallest number in v[l,r)
  T kth_smallest(int l, int r, int k) {
    assert(0 <= k && k < r - l);
    T ret = 0;
    for (int d = MAXLOG - 1; d >= 0; d--) {
      int cnt = a[d].rank(0, r) - a[d].rank(0, l);
      ll f = cnt <= k;
      ret |= T(f) << d;
      k -= cnt * f;
      tie(l, r) = succ(f, l, r, d);
    }
    return ret;
  }
  // k-th(0-indexed) largest number in v[l,r)
  T kth_largest(int l, int r, int k) {
    return kth_smallest(l, r, r - l - k - 1);
  }
  // count i s.t. (l <= i < r) && (v[i] < upper)
  int range_freq(int l, int r, T upper) {
    int ret = 0;
    for (int d = MAXLOG - 1; d >= 0; d--) {
      bool f = (upper >> d) & 1;
      if (f) ret += a[d].rank(0, r) - a[d].rank(0, l);
      tie(l, r) = succ(f, l, r, d);
    }
    return ret;
  }
  // count i s.t. (l <= i < r) && (lower <= v[i] < upper)
  int range_freq(int l, int r, T lower, T upper) {
    return range_freq(l, r, upper) - range_freq(l, r, lower);
  }
  // max v[i] s.t. (l <= i < r) && (v[i] < upper)
  T prev_value(int l, int r, T upper) {
    int cnt = range_freq(l, r, upper);
    return cnt == 0 ? T(-1) : kth_smallest(l, r, cnt - 1);
  }
  // min v[i] s.t. (l <= i < r) && (lower <= v[i])
  T next_value(int l, int r, T lower) {
    int cnt = range_freq(l, r, lower);
    return cnt == r - l ? T(-1) : kth_smallest(l, r, cnt);
  }
};
