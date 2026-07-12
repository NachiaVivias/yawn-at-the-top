#define PROBLEM "https://judge.yosupo.jp/problem/rectangle_sum"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
template <typename T>
using V = vector<T>;
#define REP(i,n) for(ll i=0; i<ll(n); i++)

#include "src/structure/2D_segtree.hpp"


int main() {
  cin.tie(0)->sync_with_stdio(0);
  
  int N, Q;
  cin >> N >> Q;
  vector<pair<int, int>> pts(N);
  vector<long long> A(N);
  for (int i = 0; i < N; i++) cin >> pts[i].first >> pts[i].second >> A[i];
  
  auto ds2 = TwoDRectangleQuery(pts);

  vector<vector<long long>> ds;
  for(auto& idx : ds2.idx){
    ds.push_back(vector<long long>(idx.size() + 1));
    for(int i=0; i<int(idx.size()); i++){
      ds.back()[i + 1] = ds.back()[i] + A[idx[i]];
    }
  }

  for(int i=0; i<N; i++){
    for(auto q : ds2.getUpdatePoints(i)){
      if(ds2.idx[q.d][q.i] != i) exit(1);
    }
  }


  for (int i = 0; i < Q; i++) {
    int l, d, r, u; cin >> l >> d >> r >> u;
    long long ans = 0;
    for(auto q : ds2.getRanges(l, r, d, u)) {
      ans += ds[q.d][q.r] - ds[q.d][q.l];
    }
    cout << ans << "\n";
  }
}
