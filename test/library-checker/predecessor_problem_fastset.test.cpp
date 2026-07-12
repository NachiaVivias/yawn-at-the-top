#define PROBLEM "https://judge.yosupo.jp/problem/predecessor_problem"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = 1ll << 60;
#define REP(i,n) for(ll i=0; i<ll(n); i++)
template <class T> using V = vector<T>;
template <class A, class B> void chmax(A& l, const B& r){ if(l < r) l = r; }
template <class A, class B> void chmin(A& l, const B& r){ if(r < l) l = r; }

#include "src/structure/fastset.hpp"


void testcase(){
  ll N, Q; cin >> N >> Q;
  string S; cin >> S;
  FS ds(N);
  REP(i,N) if(S[i] == '1') ds.insert(i);
  REP(qi,Q){
    ll c, K; cin >> c >> K;
    if(c == 0){
      ds.insert(K);
    } else if(c == 1){
      ds.erase(K);
    } else if(c == 2){
      cout << ds[K] << "\n";
    } else if(c == 3){
      cout << ds.next(K) << "\n";
    } else if(c == 4){
      cout << ds.prev(K) << "\n";
    }
  }
}

int main(){
  cin.tie(0)->sync_with_stdio(0);
  testcase();
  return 0;
}
