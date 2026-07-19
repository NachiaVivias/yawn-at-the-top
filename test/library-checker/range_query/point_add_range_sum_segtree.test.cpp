#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"

#define _GLIBCXX_DEBUG

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
template <typename T>
using V = vector<T>;

#include "src/structure/segtree.hpp"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  
  int N, Q;
  cin >> N >> Q;
  vector<long long> A(N);
  for (int i = 0; i < N; i++) cin >> A[i];

  Segtree<long long, [](long long a, long long b) { return a + b; }> segtree(A, 0);
  for (int i = 0; i < Q; i++) {
    int T;
    cin >> T;
    if (T == 0) {
      int P;
      long long X;
      cin >> P >> X;
      segtree.set(P, segtree.get(P) + X);
    } else if (T == 1) {
      int L, R;
      cin >> L >> R;
      cout << segtree.prod(L, R) << "\n";
    }
  }
}
