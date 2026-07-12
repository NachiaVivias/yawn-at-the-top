#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/challenges/sources/JAG/Regional/3355"
#define ERROR 0.000001


#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = 1ll << 60;
#define REP(i,n) for(ll i=0; i<ll(n); i++)
template<class T>
using V = vector<T>;
template<class A, class B>
bool chmax(A &a, B b){ return a < b && (a = b, true); }
template<class A, class B>
bool chmin(A &a, B b){ return b < a && (a = b, true); }

#include "src/geometry/primitive.hpp"
#include "src/geometry/halfplane_intersection.hpp"


int crossLL(L l, L m, P& r) {
  D cr1 = crs(l.vec(), m.vec()), cr2 = crs(l.vec(), l.t - m.s);
  if (sgncrs(l.vec(), m.vec()) == 0) {
    r = l.s;
    if (sgncrs(l.vec(), l.t - m.s)) return 0;
    return -1;
  }
  r = m.s + m.vec() * cr2 / cr1;
  return 1;
}

void testcase(){
  int N; cin >> N;
  double W, H; cin >> W >> H;
  vector<P> outer_vtx = { {0.0,0.0}, {W,0.0}, {W,H}, {0.0,H} };
  vector<L> outer;
  for(int i=0; i<4; i++) outer.push_back({ outer_vtx[i], outer_vtx[(i+1)%4] });
  vector<P> pts(N);
  for(int i=0; i<N; i++) cin >> pts[i].x >> pts[i].y;

  double ans = 0.0;

  for(int i=0; i<N; i++){
    auto boundary = outer;
    for(int j=0; j<N; j++) if(j != i){
      auto d = pts[j] - pts[i];
      auto mid = (pts[i] + pts[j]) / 2;
      boundary.emplace_back(mid, P(mid.x - d.y, mid.y + d.x));
    }
    auto cvx = halfplane_intersection(boundary);
    //for(auto l : cvx) cout << l.s.x << " " << l.s.y << " " << l.t.x << " " << l.t.y << endl;
    //cout << endl;
    for(int k=0; k<int(cvx.size()); k++){
      P p;
      int k2 = k + 1;
      if(k2 == int(cvx.size())) k2 = 0;
      if(crossLL(cvx[k], cvx[k2], p)) chmax(ans, (p - pts[i]).norm());
    }
  }

  cout << sqrt(ans) << "\n";
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cout.precision(20);
    cout << fixed;
    testcase();
    return 0;
}
