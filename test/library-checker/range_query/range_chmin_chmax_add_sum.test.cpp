#define PROBLEM "https://judge.yosupo.jp/problem/range_chmin_chmax_add_range_sum"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = 1ll << 60;
#define REP(i,n) for(ll i=0; i<ll(n); i++)
template<class T>
using V = vector<T>;
template<class A, class B>
bool chmax(A &a, B b){ return a < b && (a = b, true); }
template<class A, class B>
bool chmin(A &a, B b){ return b < a && (a = b, true); }

#include "src/structure/range_chmin_chmax_add_sum_beats.hpp"

template <class S, class F, S op(S, S),
          F composition(F, F), S mapping(F, S)>
struct LazySegtree {
  int n, s, log;
  S e;
  F id;
  vector<S> d;
  vector<F> lz;

  void update(int k) {
    d[k] = op(d[2 * k], d[2 * k + 1]);
  }
  void push(int k) {
    all_apply(2 * k, lz[k]);
    all_apply(2 * k + 1, lz[k]);
    lz[k] = id;
  }
  void all_apply(int k, F f) {
    d[k] = mapping(f, d[k]);
    if (k < s) lz[k] = composition(f, lz[k]);
    if(d[k].fail) push(k), update(k);
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
    p += s;
    for (int i = log; i >= 1; i--) push(p >> i);
    d[p] = x;
    for (int i = 1; i <= log; i++) update(p >> i);
  }
  S get(int p) {
    p += s;
    for (int i = log; i >= 1; i--) push(p >> i);
    return d[p];
  }
  S prod(int l, int r) {
    if (l == r) return e;
    l += s, r += s;
    for (int i = log; i >= 1; i--) {
      if (((l >> i) << i) != l) push(l >> i);
      if (((r >> i) << i) != r) push((r - 1) >> i);
    }
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
    l += s, r += s;
    for (int i = log; i >= 1; i--) {
      if (((l >> i) << i) != l) push(l >> i);
      if (((r >> i) << i) != r) push((r - 1) >> i);
    }
    {
      int l2 = l, r2 = r;
      while (l < r) {
        if (l & 1) all_apply(l++, f);
        if (r & 1) all_apply(--r, f);
        l >>= 1, r >>= 1;
      }
      l = l2, r = r2;
    }
    for (int i = 1; i <= log; i++) {
      if (((l >> i) << i) != l) update(l >> i);
      if (((r >> i) << i) != r) update((r - 1) >> i);
    }
  }
  template <class G>
  int max_right(int l, G g) {
    if (l == n) return n;
    l += s;
    for (int i = log; i >= 1; i--) push(l >> i);
    S sm = e;
    do {
      while (l % 2 == 0) l >>= 1;
      if (!g(op(sm, d[l]))) {
        while (l < s) {
          push(l);
          l = 2 * l;
          if (g(op(sm, d[l]))) {
            sm = op(sm, d[l]);
            l++;
          }
        }
        return l - s;
      }
      sm = op(sm, d[l]);
      l++;
    } while ((l & -l) != l);
    return n;
  }
  template <bool (*g)(S)>
  int min_left(int r) {
    return min_left(r, [](S x) { return g(x); });
  }
  template <class G>
  int min_left(int r, G g) {
    if (r == 0) return 0;
    r += s;
    for (int i = log; i >= 1; i--) push((r - 1) >> i);
    S sm = e;
    do {
      r--;
      while (r > 1 && (r % 2)) r >>= 1;
      if (!g(op(d[r], sm))) {
        while (r < s) {
          push(r);
          r = 2 * r + 1;
          if (g(op(d[r], sm))) {
            sm = op(d[r], sm);
            r--;
          }
        }
        return r + 1 - s;
      }
      sm = op(d[r], sm);
    } while ((r & -r) != r);
    return 0;
  }
};


int main(){
  cin.tie(0)->sync_with_stdio(0);
  long long N, Q; cin >> N >> Q;
  //if(N == 5 && Q == 7) return;
  vector<long long> A(N); for(int i=0; i<N; i++) cin >> A[i];
  vector<Elem> elems(N, e());
  for(long long i=0; i<N; i++){
    elems[i].l.x = elems[i].r.x = elems[i].sum = A[i];
    elems[i].cnt = 1;
    elems[i].fail = 0;
    elems[i].l.c = elems[i].r.c = 1;
  }
  auto ds = LazySegtree<Elem, F, op, composition, mapping>(elems, e(), id());
  for(long long qi=0; qi<Q; qi++){
    long long t; cin >> t;
    if(t == 0){
      long long l, r, b; cin >> l >> r >> b;
      ds.apply(l, r, { -INF, b, 0 });
    } else if(t == 1){
      long long l, r, b; cin >> l >> r >> b;
      ds.apply(l, r, { b, INF, 0 });
    } else if(t == 2){
      long long l, r, b; cin >> l >> r >> b;
      ds.apply(l, r, { -INF, INF, b });
    } else {
      long long l, r; cin >> l >> r;
      cout << ds.prod(l, r).sum << "\n";
    }
  }
  return 0;
}
