#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/challenges/sources/JAG/Summer/2292"

#include <bits/stdc++.h>
using namespace std;
template <class T> using V = vector<T>;
using ll = long long;
#define REP(i,n) for(ll i=0; i<ll(n); i++)

#include "src/string/palindromic_tree.hpp"
ll cnt[1000000][2] = {};

int nodeIdx(PalNode* p){ return p - pool.data(); }

void testcase(){
  string S, T; cin >> S >> T;
  PalTree pt;
  for(int t=0; t<2; t++){
    pt.v = pt.n1;
    pt.s = {};
    for(size_t i=0; i<S.size(); i++){
      int c = S[i] - 'A';
      pt.add_char(c);
      cnt[nodeIdx(pt.v)][t] += 1;
    }
    swap(S, T);
  }
  ll ptr = poolptr - pool.data();
  for(int i=ptr-1; i>=2; i--) for(int t=0; t<2; t++) cnt[nodeIdx(pool[i].li)][t] += cnt[i][t];
  ll ans = 0;
  for(int i=2; i<ptr; i++) ans += cnt[i][0] * cnt[i][1];
  cout << ans << "\n";
}

int main(){
  cin.tie(0)->sync_with_stdio(0);
  testcase();
  return 0;
}