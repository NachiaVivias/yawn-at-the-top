// f(i,c)はc=C[i-1]の時にA[i],B[i]を返す関数（i=0の時はcは何でもよい）
template <class D>
V<D> relaxed_convolution(int N, auto f) {
  V<D> R(N, 0), A(N), B(N), C;
  D c = 0;
  REP(i, N) {
    tie(A[i], B[i]) = f(i, c);
    for (int p = 1; (i + 2) % p == 0; p *= 2) {
      if (p == i + 2) break;
      auto calc = [&](int la, int ra, int lb, int rb) {
        C = multiply(V<D>(A.begin() + la, A.begin() + ra),
            V<D>(B.begin() + lb, B.begin() + rb));
        REP(j, C.size()) if (la + lb + j < N)
          R[la + lb + j] += C[j];
      };
      if (p * 2 != i + 2)
        calc(p - 1, 2 * p - 1, i + 1 - p, i + 1);
      calc(i + 1 - p, i + 1, p - 1, 2 * p - 1);
    }
    c = R[i];
  }
  return R;
}