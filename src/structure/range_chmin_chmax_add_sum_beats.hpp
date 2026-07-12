struct F {
  ll l, r, a;
};
template <class Cmp, ll INF>
struct ChminElem {
  ll x = INF, y = INF, c = 0;
  ChminElem op(ChminElem r) const {
    if(x == r.x)
      return { x, min(y, r.y, Cmp()), c + r.c };
    if(Cmp()(x, r.x))
      return { x, min(y, r.x, Cmp()), c };
    return { r.x, min(x, r.y, Cmp()), r.c };
  }
  void apply(F f){
    if(x != INF) x = max(f.l, min(f.r, x)) + f.a;
    if(y != INF) y = max(f.l, min(f.r, y)) + f.a;
  }
};
struct Elem {
  ChminElem<less<ll>, INF> l;
  ChminElem<greater<ll>, -INF> r;
  ll cnt = 0, sum = 0;
  ll fail = 0;
};
Elem op(Elem l, Elem r){
///  Elem res;
///  res.l = l.l.op(r.l);
///  res.r = l.r.op(r.r);
///  res.cnt = l.cnt + r.cnt;
///  res.sum = l.sum + r.sum;
///  res.fail = 0;
///  return res;
  return { l.l.op(r.l), l.r.op(r.r), l.cnt + r.cnt, l.sum + r.sum, 0 };
}
F composition(F f, F x){
  if(f.l != -INF){
    f.l -= x.a;
    chmax(x.l, f.l);
    chmax(x.r, f.l);
  }
  if(f.r != INF){
    f.r -= x.a;
    chmin(x.l, f.r);
    chmin(x.r, f.r);
  }
  x.a += f.a;
  return x;
}
Elem mapping(F f, Elem x){
  x.fail = 1;
  if(f.l != -INF && x.l.y <= f.l) return x;
  if(f.r != INF && x.r.y >= f.r) return x;
  if(x.l.x < f.l) x.sum += (f.l - x.l.x) * x.l.c;
  if(x.r.x > f.r) x.sum += (f.r - x.r.x) * x.r.c;
  x.sum += f.a * x.cnt;
  x.l.apply(f);
  x.r.apply(f);
  x.fail = 0;
  return x;
}
Elem e(){ return Elem(); }
F id(){ return { -INF, INF, 0 }; }