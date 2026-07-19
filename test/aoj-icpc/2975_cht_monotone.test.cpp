#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/challenges/sources/JAG/Summer/2975"
#define ERROR 0.000000001

#define _GLIBCXX_DEBUG

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = 1ll << 60;
#define REP(i, n) for(ll i=0; i <ll(n); i++)
template <class T> using V = vector<T>;
template <class A, class B>
bool chmax(A &a, B b) { return a < b && (a=b, true); }
template <class A, class B>
bool chmin(A &a, B b) { return b < a && (a=b, true); }

#include "src/convex/cht_monotone.hpp"

using D = long double;
struct F {
  D a, b;
  D operator()(D x){ return a * x + b; }
};

void cross(F a, F b, D& xa, D& xb){
  xa = xb = -(a.b - b.b) / (a.a - b.a);
}

void testcase(){
  ll N; cin >> N;
  ll offX, offZ; cin >> offX >> offZ;
  V<ll> X(N), Z(N);
  REP(i,N) cin >> X[i] >> Z[i];
  REP(i,N) X[i] -= offX, Z[i] -= offZ;

  auto crossX = [](F l, F r){
    return -(r.b - l.b) / (r.a - l.a);
  };

  V<double> ans(N, 1.0e100);
  REP(t,2){
    V<F> lines;
    REP(i,N) if(X[i] > 0 && Z[i] < 0) lines.push_back({ (D)Z[i], (D)X[i] });
    sort(lines.begin(), lines.end(), [](auto l, auto r){ return l.a > r.a; });

    CHTMonotone cht((D)0, (D)3e9, F{ 0, 0 });
    for(auto a : lines) cht.add(a, [](F f, D x){ return f(x); }, cross);
    auto A = vector(cht.a.begin(), cht.a.end());

    REP(i,N){
      F ln = { Z[i], X[i] };
      if(X[i] <= 0){
        if(Z[i] <= A.back().f.a) continue;
        ll l = -1, r = A.size();
        while(l + 1 < r){
          ll m = l + (r - l) / 2;
          if(ln.a <= A[m].f.a){ l = m; continue; }
          auto cr = crossX(A[m].f, ln);
          chmin(ans[i], cr);
          if(cr < A[m].l){ r = m; continue; }
          if(A[m].r <= cr){ l = m; continue; }
          break;
        }
      }
    }
    
    for(auto& a : X) a *= -1;
    for(auto& a : Z) a *= -1;
  }

  cout.precision(20);
  for(auto a : ans){
    if(a > 1.0e16){ cout << "-1\n"; continue; }
    cout << a << "\n";
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  testcase();
  return 0;
}

