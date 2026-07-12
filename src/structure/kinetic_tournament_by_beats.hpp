struct Line {
  ll a, b;
  ll cross(Line r) const {
    return r.a <= a ? INF : (b - r.b) / (r.a - a) + 1;
  }
};
struct S {
  Line max;
  ll melt, fail = 0;
};
S e(){ return { {0,-INF}, INF, 0 }; }
S op(S l, S r){
  S res;
  res.melt = min(l.melt, r.melt);
  bool fl = l.max.b < r.max.b;
  res.max = fl ? r.max : l.max;
  if(fl) chmin(res.melt, r.max.cross(l.max));
  if(!fl) chmin(res.melt, l.max.cross(r.max));
  return res;
}
struct F {
  ll dt;
};
F id(){ return { 0 }; }
S mapping(F f, S x){
  x.melt -= f.dt;
  x.max.b += f.dt * x.max.a;
  if(x.melt <= 0) x.fail = 1;
  return x;
}
F composition(F f, F x){
  x.dt += f.dt;
  return x;
}