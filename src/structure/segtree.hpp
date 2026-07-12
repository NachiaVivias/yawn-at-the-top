template <class S, S op(S, S)>
struct Segtree {
  int n, s;
  S e;
  V<S> d;
  Segtree() = default;
  Segtree(unsigned n, S e) : n(n), s(bit_ceil(n)), e(e) {
    d.assign(2 * s, e);
  }
  Segtree(const vector<S>& v, S e) : Segtree(v.size(), e) {
    ranges::copy(v, d.begin() + s);
    for (int i = s - 1; i >= 1; i--)
      d[i] = op(d[2 * i], d[2 * i + 1]);
  }
  void set(int p, S x) {
    d[p += s] = x;
    while ((p >>= 1) >= 1)
      d[p] = op(d[2 * p], d[2 * p + 1]);
  }
  S get(int p) {
    return d[p + s];
  }
  S prod(int l, int r) {
    S sml = e, smr = e;
    l += s, r += s;
    while (l < r) {
      if (l & 1) sml = op(sml, d[l++]);
      if (r & 1) smr = op(d[--r], smr);
      l >>= 1, r >>= 1;
    }
    return op(sml, smr);
  }
  template <class G>
  int max_right(int l, G f) {
    if (l == n) return n;
    l += s;
    S sm = e;
    while (1) {
      while (l % 2 == 0) l >>= 1;
      S t = op(sm, d[l]);
      if (!f(t)) break;
      sm = t;
      if (l++, (l & -l) == l) return n;
    }
    while (l < s) {
      l = 2 * l;
      if (S t = op(sm, d[l]); f(t)) sm = t, l++;
    }
    return l - s;
  }
  template <class F>
  int min_left(int r, F f) {
    if (r == 0) return 0;
    r += s;
    S sm = e;
    while (1) {
      r--;
      while (r > 1 && (r % 2)) r >>= 1;
      S t = op(d[r], sm);
      if (!f(t)) break;
      sm = t;
      if ((r & -r) == r) return 0;
    }
    while (r < s) {
      r = 2 * r + 1;
      if (S t = op(d[r], sm); f(t)) sm = t, r--;
    }
    return r + 1 - s;
  }
};
