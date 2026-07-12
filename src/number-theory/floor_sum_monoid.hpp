// 1 <= A, 0 <= B
template<class Int, class S, S op(const S&, const S&)>
S FloorSumMonoid(Int N, Int M, Int A, Int B, S X, S Y, S e){
  auto pow = [&](S r, S a, Int i){
    do {
      if(i % 2) r = op(r, a);
      a = op(a, a);
    } while(i /= 2);
    return r;
  };
  S L = e, R = e;
  Int C = (A * N + B) / M;
  while(1){
    Int qa = A / M, qb = B / M;
    A %= M;
    B %= M;
    X = pow(X, Y, qa);
    L = pow(L, Y, qb);
    C -= qa * N + qb;
    if(C == 0) break;
    Int D = (M * C - B - 1) / A + 1;
    R = op(pow(Y, X, N - D), R);
    B = M - B - 1 + A;
    N = C - 1; C = D;
    swap(M, A);
    swap(X, Y);
  }
  return op(pow(L, X, N), R);
}
// struct S { ll x, y, sum; };
// S op(const S& l, const S& r){
//   return { l.x + r.x, l.y + r.y, l.sum + r.sum + l.y * r.x };
// }
// S e = { 0,0,0 };