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

#include "src/convex/cht_base.hpp"

void testcase(){
  ll N; cin >> N;
  ll offX, offZ; cin >> offX >> offZ;
  V<ll> X(N), Z(N);
  REP(i,N) cin >> X[i] >> Z[i];
  REP(i,N) X[i] -= offX, Z[i] -= offZ;

  V<double> ans(N, 1.0e100);
  REP(t,2){
    V<Line> lines;
    lines.push_back({ 0, 0 });
    REP(i,N) if(X[i] < 0 && Z[i] > 0) lines.push_back({ Z[i], X[i] });
    sort(lines.begin(), lines.end());

    V<Line> exts;
    for(auto a : lines){
      while(exts.size() >= 2){
        auto b = exts[exts.size() - 1];
        auto c = exts[exts.size() - 2];
        if(b < a && c.crossX(b) < b.crossX(a)) break;
        exts.pop_back();
      }
      exts.push_back(a);
    }
    V<Frac> pts;
    pts.push_back({0,1});
    for(int i=0; i+1<exts.size(); i++){
      pts.push_back(exts[i].crossX(exts[i+1]));
    }
    pts.push_back(InfFrac);

    REP(i,N){
      Line ln = { Z[i], X[i] };
      if(X[i] >= 0){
        if(exts.back().a <= Z[i]) continue;
        ll l = -1, r = exts.size();
        while(1){
          if(l + 1 == r){
            chmin(ans[i], double(pts[r].a) / double(pts[r].b));
            break;
          }
          ll m = (l + r + 2) / 2 - 1;
          if(exts[m] <= ln){ l = m; continue; }
          auto cr = exts[m].crossX(ln);
          if(cr <= pts[m]){ r = m; continue; }
          if(pts[m+1] <= cr){ l = m; continue; }
          chmin(ans[i], double(cr.a) / double(cr.b));
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

