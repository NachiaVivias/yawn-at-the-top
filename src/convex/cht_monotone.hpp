/// Original : Nachia
template<class Pos, class F>
struct CHTMonotone {
  struct Q { Pos l, r; F f; };
  deque<Q> a;
  CHTMonotone(Pos l, Pos r, F inf) : a({{ l, r, inf }}) {}
  void add(F f, auto fx, auto cross){
    Pos l = a[0].l, r = a.back().r;
    Q qf = { l, r, f };
    if(fx(f, r) < fx(a.back().f, r)){
      do{
        Q& q = a.back();
        if(fx(f, q.l) < fx(q.f, q.l)) continue;
        cross(q.f, f, q.r = q.l, qf.l = r);
        break;
      } while(a.pop_back(), a.size());
      a.push_back(qf);
    }
    else if(fx(f, l) < fx(a[0].f, l)){
      do{
        Q& q = a.front();
        if(fx(f, q.r) < fx(q.f, q.r)) continue;
        cross(f, q.f, qf.r = l, q.l = q.r);
        break;
      } while(a.pop_front(), a.size());
      a.push_front(qf);
    }
  }
  F query(Pos x){
// clang-format off
    return ranges::partition_point(a,
      [x](Q& f){ return f.r < x; })->f;
// clang-format on
  }
  F query_inc(Pos x){
    while(a[0].r < x) a.pop_front();
    a[0].l = x;
    return a[0].f;
  }
  F query_dec(Pos x){
    while(x < a.back().l) a.pop_back();
    a.back().r = x;
    return a.back().f;
  }
};
// struct F { ll a, b; };
// auto fx = [&](F f, ll x){ return f.a * x + f.b; };
// void cross(F a, F b, ll& xa, ll& xb){
//   while(abs(xa - xb) > 1){
//     Pos x = xa + (xb - xa) / 2;
//     (a(x) < b(x) ? xa : xb) = x;
//   }
// }
// void cross(F a, F b, double& xa, double& xb){
//   xa = xb = -(a.b - b.b) / (a.a - b.a);
// }
