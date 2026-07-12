template <class S, class F, S op(S, S),
          F composition(F, F), S mapping(F, S)>
struct LazySegtree {
  int n, s, log;
  S e;
  F id;
  V<S> d;
  V<F> lz;

  void update(int k) {
    d[k] = op(d[2 * k], d[2 * k + 1]);
  }
  void all_apply(int k, F f) {
    d[k] = mapping(f, d[k]);
    if (k < s) lz[k] = composition(f, lz[k]);
    // if(d[k].fail) push(k), update(k);
  }
  void push(int k) {
    all_apply(2 * k, lz[k]);
    all_apply(2 * k + 1, lz[k]);
    lz[k] = id;
  }
  void pushx(int p){
    for (int i = log; i >= 1; i--) push(p >> i);
  }
  void updx(int p){
    for (int i = 1; i <= log; i++) update(p >> i);
  }
  
  LazySegtree() = default;
  LazySegtree(unsigned n, S e, F id)
      : n(n), s(bit_ceil(n)), e(e), id(id) {
    log = countr_zero((unsigned)s);
    d.assign(2 * s, e), lz.assign(s, id);
  }
  LazySegtree(const vector<S>& v, S e, F id)
      : LazySegtree(v.size(), e, id) {
    ranges::copy(v, d.begin() + s);
    for (int i = s - 1; i >= 1; i--) update(i);
  }
  void set(int p, S x) {
    pushx(p += s);
    d[p] = x;
    updx(p);
  }
  S get(int p) {
    pushx(p += s);
    return d[p];
  }
  S prod(int l, int r) {
    if (l == r) return e;
    pushx(l += s), pushx((r += s) - 1);
    S sml = e, smr = e;
    while (l < r) {
      if (l & 1) sml = op(sml, d[l++]);
      if (r & 1) smr = op(d[--r], smr);
      l >>= 1, r >>= 1;
    }
    return op(sml, smr);
  }
  void apply(int l, int r, F f) {
    if (l == r) return;
    if((l += s) > s) pushx(l - 1);
    if((r += s) < s * 2) pushx(r);
    int l2 = l, r2 = r;
    while (l < r) {
      if (l & 1) all_apply(l++, f);
      if (r & 1) all_apply(--r, f);
      l >>= 1, r >>= 1;
    }
    if(l2 > s) updx(l2 - 1);
    if(r2 < s * 2) updx(r2);
  }
  template <class G>
  int max_right(int l, G f) {
    if (l == n) return n;
    pushx(l += s);
    S sm = e;
    while (1) {
      while (l % 2 == 0) l >>= 1;
      S t = op(sm, d[l]);
      if (!f(t)) break;
      sm = t;
      if (l++, (l & -l) == l) return n;
    }
    while (l < s) {
      push(l);
      l = 2 * l;
      if (S t = op(sm, d[l]); f(t)) sm = t, l++;
    }
    return l - s;
  }
  template <class G>
  int min_left(int r, G f) {
    if (r == 0) return 0;
    pushx((r += s) - 1);
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
      push(r);
      r = 2 * r + 1;
      if (S t = op(d[r], sm); f(t)) sm = t, r--;
    }
    return r + 1 - s;
  }
};
