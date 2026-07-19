#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"

#define _GLIBCXX_DEBUG

#include <bits/stdc++.h>
using namespace std;
template <typename T>
using V = vector<T>;

#include "src/structure/fenwick.hpp"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  
  int N, Q;
  cin >> N >> Q;

  Fenwick<long long> ds(N);
  for(int i=0; i<N; i++){
    long long a; cin >> a;
    ds.add(i, a);
  }

  for (int i = 0; i < Q; i++) {
    int T;
    cin >> T;
    if (T == 0) {
      int P;
      long long X;
      cin >> P >> X;
      ds.add(P, X);
    } else if (T == 1) {
      int L, R;
      cin >> L >> R;
      cout << ds.sum(L, R) << "\n";
    }
  }
}
