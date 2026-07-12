const Mint zero(0);
const Mint one(1);
bool iszero(Mint x) {
  return x.v == 0;
}
template <class T>
struct Matrix {
  int H, W;
  V<V<T>> a;
  Matrix(V<V<T>> v) : H(v.size()), W(v[0].size()), a(move(v)) {
  }
  Matrix(int H = 0, int W = 0) : H(H), W(W), a(H, V<T>(W)) {
  }
  static Matrix E(int n) {
    Matrix a(n, n);
    REP(i, n) a.set(i, i, 1);
    return a;
  }
  T at(int i, int j) const {
    return a[i][j];
  }
  void set(int i, int j, T v) {
    a[i][j] = v;
  }
  /*
  左から var 列が階段行列になるように、行基本変形を施す。
  (e.g. 逆⾏列 は右に単位⾏列おいてから掃き出す)
  rank,determinant を返す。 in placeに更新されることに注意
  */
  pair<int, T> sweep(int var) {
    int i = 0, rank = 0;
    T d = one;
    REP(j, var) {
      for (i = rank; i < H && iszero(a[i][j]); ) i++;
      if (i == H) continue;
      if (i != rank) d = -d;
      swap(a[i], a[rank]);
      i = rank++;
      T t = a[i][j];
      REP(k, W) a[i][k] /= t;
      d *= t;
      REP(k, H) if (k != i) {
        t = a[k][j];
        REP(l, W) a[k][l] -= a[i][l] * t;
      }
    }
    if (H != W || rank != H) d *= zero;
    return {rank, d};
  }
  Matrix tr() {
    auto B = Matrix(W, H);
    REP(i, H) REP(j, W) B.set(j, i, at(i, j));
    return B;
  }
  int getrank() {
    auto B = H < W ? *this : tr();
    return B.sweep(B.W).first;
  }
  T getdet() {
    return Matrix(*this).sweep(W).second;
  }
  Matrix inv() {
    assert(H == W);
    int N = H;
    Matrix X(N, 2 * N), B(N, N);
    REP(i, N) REP(j, N) X.set(i, j, a[i][j]);
    REP(i, N) X.set(i, i + N, one);
    if (X.sweep(N).first < N) return Matrix();
    REP(i, N) REP(j, N) B.set(i, j, X.at(i, j + N));
    return B;
  }
  friend ostream& operator<<(ostream& o, const Matrix& A) {
    REP(i, A.H) {
      REP(j, A.W) o << A.a[i][j] << " ";
      o << endl;
    }
    return o;
  }
};
