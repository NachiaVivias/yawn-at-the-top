template<int BUFSIZE, class S, S op(S, S), S e(), class F, S mapping(F, S), F comp(F, F), F id()>
struct Node {
  using np = Node*;
  using pnp = pair<np, np>;
  np l, r;
  S sum;
  F lz;
  int dep;
  static inline Node buf[BUFSIZE];
  static inline int pbuf = 0;
  static np alloc() { return buf + pbuf++; }
  static int mdep(np a, np b){
    return max(a->dep, b->dep) + 1;
  }
  static np mid(np l, np r, F lz = id()) {
    auto v = alloc();
    *v = { l, r, mapping(lz, op(l->sum, r->sum)), lz, mdep(l, r) };
    return v;
  }
  np apply(F f) {
    if(l) return mid(l, r, comp(f, lz));
    return &(*alloc() = {0, 0, mapping(f, sum), id(), 0});
  }
  static pnp mg1(np a, np b, np c) {
    if (abs(mdep(a, b) - c->dep) <= 1) return {mid(a, b), c};
    if (abs(mdep(b, c) - a->dep) <= 1) return {a, mid(b, c)};
    return {mid(a, b->l->apply(b->lz)), mid(b->r->apply(b->lz), c)};
  }
  static pnp mg2(np a, np b, F alz, F blz) {
    if (a->dep < b->dep) {
      blz = comp(blz, b->lz);
      auto [xl, xr] = mg2(a, b->l, alz, blz);
      return mg1(xl, xr, b->r->apply(blz));
    }
    if (a->dep > b->dep) {
      alz = comp(alz, a->lz);
      auto [xl, xr] = mg2(a->r, b, alz, blz);
      return mg1(a->l->apply(alz), xl, xr);
    }
    return {a->apply(alz), b->apply(blz)};
  }
  static np merge(np a, np b) {
    if (!a || !b) return a ? a : b;
    auto [l, r] = mg2(a, b, id(), id());
    return mid(l, r);
  }
  pnp split(const auto& det, S off = e(), F f = id()) {
    if (det(op(off, sum))) return {apply(f), 0};
    if (!l) return {0, apply(f)};
    f = comp(f, lz);
    if (S t = op(off, l->sum); det(t)) {
      auto [gl, gr] = r->split(det, t, f);
      return {merge(l->apply(f), gl), gr};
    }
    auto [gl, gr] = l->split(det, off, f);
    return {gl, merge(gr, r->apply(f))};
  }
  static np build(const vector<S>& arr) {
    vector<np> tmp;
    for (auto v : arr){
      tmp.push_back(alloc());
      *tmp.back() = { 0, 0, v, id(), 0 };
    }
    int n = tmp.size();
    for (int s = 1; s < n; s *= 2)
      for (int i = 0; i + s < n; i += 2 * s)
        tmp[i] = merge(tmp[i], tmp[i + s]);
    return tmp[0];
  }
};