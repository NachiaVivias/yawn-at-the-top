#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/challenges/sources/ICPC/Regional/1421"


#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = 1ll << 60;
#define REP(i, n) for (ll i=0; i<ll(n); i++)
template <class T> using V = vector<T>;
template<class A, class B>
bool chmax(A &a, B b) { return a < b && (a = b, true); }
template<class A, class B>
bool chmin(A &a, B b) { return b < a && (a = b, true); }

#include "src/string/aho-corasick-direct-link.hpp"

void testcase(){
  string S; cin >> S;
  ll N; cin >> N;
  auto [ac, P] = AhoCorasick(V<string>{S});

  ll K = ac.size();
  V<ll> score(K);
  for(ll i=1; i<K; i++) score[i] = score[ac[i].li] + 1;

  V<ll> dp(K, -INF); dp[0] = 0;
  REP(i,N){
    V<ll> nx(K, -INF);
    REP(a,K) REP(c,26) chmax(nx[ac[a].nx[c]], dp[a]);
    REP(a,K) nx[a] += score[a];
    swap(dp, nx);
  }

  ll ans = *max_element(dp.begin(), dp.end());
  cout << ans << "\n";
}

int main(){
  cin.tie(0)->sync_with_stdio(0);
  testcase();
  return 0;
}
