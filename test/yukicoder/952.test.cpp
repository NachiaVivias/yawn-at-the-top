#define PROBLEM "https://yukicoder.me/problems/no/952"

/*

No.952 危険な火薬庫
オンライン行最小値

*/

#include "src/common/template.hpp"
#include "src/convex/cht_monotone.hpp"


void testcase(){
  ll N; cin >> N;
  V<ll> A(N); REP(i,N) cin >> A[i];
  V<ll> S(N+1); REP(i,N) S[i+1] = S[i] + A[i];

  V<ll> dp(N+2, INF); dp[0] = 0;
  V<ll> ans(N);

  struct F{
    ll l;
    V<ll>& dp, &S;
    ll operator()(ll r){
      ll wt = 0;
      if(l < r) wt = S[r-1] - S[l];
      return dp[l] + wt * wt;
    };
  };

  auto cross = [&](auto& a, auto& b, ll& xa, ll& xb){
        while(abs(xa - xb) > 1){
          ll x = xa + (xb - xa) / 2;
          (a(x) < b(x) ? xa : xb) = x;
        }
      };

  REP(k,N){
    V<ll> nx(N+2, INF);
    auto cht = CHTMonotone(0ll, N+1, F{0,dp,S});
    REP(i,N+1){
      nx[i+1] = cht.query_inc(i+1)(i+1);
      cht.add({i,dp,S}, [](auto& f, auto& x){ return f(x); }, cross);
      nx[i+1] = cht.query_inc(i+1)(i+1);
    }
    swap(dp, nx);
    ans[N-1-k] = dp[N+1];
  }
  REP(i,N) cout << ans[i] << "\n";
}

int main(){
  cin.tie(0)->sync_with_stdio(0);
  testcase();
  return 0;
}
