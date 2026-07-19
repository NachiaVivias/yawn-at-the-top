#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/challenges/sources/PCK/Prelim/0439"

// maybe slows down std::sort
// #define _GLIBCXX_DEBUG

#include <bits/stdc++.h>
#include <cassert>
using namespace std;
using ll = long long;
const ll INF = 1ll << 60;
#define REP(i, n) for (ll i=0; i<ll(n); i++)
template <class T> using V = vector<T>;
template<class A, class B>
bool chmax(A &a, B b) { return a < b && (a = b, true); }
template<class A, class B>
bool chmin(A &a, B b) { return b < a && (a = b, true); }

#include "src/tree/hld.hpp"

void testcase(){
  ll N; cin >> N;
  V<ll> C(N);
  V<V<int>> col(N);
  REP(i,N){
    ll x; cin >> x;
    col[x-1].push_back(i);
    C[i] = x - 1;
  }
  V<V<int>> g(N);
  REP(i,N-1){
    ll u,v; cin >> u >> v; u--; v--;
    g[u].push_back(v);
    g[v].push_back(u);
  }

  auto hld = HLD(N, g, 0);
  V<ll> ans(N, INF), dp(N), dpm(N), dph(N);
  REP(c,N) if(col[c].size()){
    auto [vs, e] = hld.ComputeTree(col[c]);
    for(auto v : vs){ dp[v] = dph[v] = INF; }
    for(auto v : col[c]) dp[v] = 0;

    ll n = vs.size();
    for(ll i=n-2; i>=0; i--){
      auto [u,v] = e[i];
      chmin(dp[u], dp[v] + hld.dep[v] - hld.dep[u]);
    }
    
    for(auto v : vs){ dpm[v] = INF; }
    for(ll i=0; i<=n-2; i++){
      auto [u,v] = e[i];
      if(C[u] == c) chmin(dph[v], hld.dep[v] - hld.dep[u]);
      chmin(dph[v], dpm[u] + hld.dep[v] - hld.dep[u]);
      chmin(dpm[u], dp[v] + hld.dep[v] - hld.dep[u]);
    }
    for(auto v : vs){ dpm[v] = INF; }
    for(ll i=n-2; i>=0; i--){
      auto [u,v] = e[i];
      chmin(dph[v], dpm[u] + hld.dep[v] - hld.dep[u]);
      chmin(dpm[u], dp[v] + hld.dep[v] - hld.dep[u]);
    }
    
    for(ll i=0; i<=n-2; i++){
      auto [u,v] = e[i];
      chmin(dph[v], dph[u] + hld.dep[v] - hld.dep[u]);
    }


    for(auto [u,v] : e){
      if(C[u] == c) chmin(ans[u], dp[v] + hld.dep[v] - hld.dep[u]);
    }
    for(ll v : col[c]) chmin(ans[v], dph[v]);
  }

  REP(i,N) cout << ans[i] << "\n";
}

int main(){
  cin.tie(0)->sync_with_stdio(0);
  testcase();
  return 0;
}
