// i=0,1,...,N-1についてf(a+i*b)=Y[i]となるとき、f(x)を返す
Mint Interpolation_AP(int N, Mint a, Mint b, V<Mint> Y, Mint x) {
  Mint f = 1;
  REP(i, N) if(i) f *= b * i;
  f = f.inv();  // 逆元
  V<Mint> C = Y, L(N + 1, 1), R(N + 1, 1);
  for (int i = N - 2; i >= 0; i -= 2) C[i] = -C[i];
  for (int i = N - 1; i >= 0; --i) {
    C[i] *= f;
    C[N - 1 - i] *= f;
    f *= b * i;
  }
  REP(i, N) {
    L[i + 1] = L[i] * (x - (a + b * i));
    R[N - 1 - i] = R[N - i] * (x - (a + b * (N - 1 - i)));
  }
  Mint s = 0;
  REP(i, N) s += L[i] * R[i + 1] * C[i];
  return s;
}

// i=0,1,...,N-1についてf(X[i])=Y[i]となるとき、f(x)を返す
Mint Interpolation(int N, V<Mint> X, V<Mint> Y, Mint x) {
  V<Mint> C(N, 1), L(N + 1, 1), R(N + 1, 1);
  REP(i, N) REP(j, N) if(i != j) C[i] *= X[i] - X[j];
  REP(i, N) C[i] = C[i].inv() * Y[i];  // 逆元
  REP(i, N) {
    L[i + 1] = L[i] * (x - X[i]);
    R[N - 1 - i] = R[N - i] * (x - X[N - 1 - i]);
  }
  Mint s = 0;
  REP(i, N) s += L[i] * R[i + 1] * C[i];
  return s;
}