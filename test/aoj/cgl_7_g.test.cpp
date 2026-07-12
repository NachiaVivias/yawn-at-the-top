#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/7/CGL_7_G"
#define ERROR 0.00001

#include <bits/stdc++.h>
using namespace std;
template <class T>
using V = vector<T>;

#include "src/geometry/primitive.hpp"
#include "src/geometry/intersect.hpp"

using Pol = V<P>;
struct C {
  P p;
  D r;
  C(P _p = P(), D _r = D()) : p(_p), r(_r) {
  }
};
#include "src/geometry/circle_tangent.hpp"

int main() {
    auto input_cir = [&] {
        P c; D r; cin >> c.x >> c.y >> r;
        return C(c, r);
    };
    C c1 = input_cir(), c2 = input_cir();
    cout << fixed << setprecision(10);
    vector<P> ans;
    L l0, l1;
    int num;
    num = tangent(c1, c2, l0, l1, false);
    if(num >= 1) ans.push_back(l0.s);
    if(num >= 2) ans.push_back(l1.s);
    num = tangent(c1, c2, l0, l1, true);
    if(num >= 1) ans.push_back(l0.s);
    if(num >= 2) ans.push_back(l1.s);
    sort(ans.begin(), ans.end(), [](P a, P b) {
        return a.x == b.x ? a.y < b.y : a.x < b.x;
    });
    for(auto p : ans) cout << p.x << " " << p.y << endl;
}
