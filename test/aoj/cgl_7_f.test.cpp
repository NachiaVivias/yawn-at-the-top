#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/7/CGL_7_F"
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
    P p; cin >> p.x >> p.y;
    P c; D r; cin >> c.x >> c.y >> r;
    C cir(c, r);
    P q0, q1;
    assert(tangent(cir, p, q0, q1) >= 1);
    if(q0.x > q1.x) swap(q0, q1);
    if(q0.x == q1.x && q0.y > q1.y) swap(q0, q1);
    cout << fixed << setprecision(10) << q0.x << " " << q0.y << "\n" << q1.x << " " << q1.y << endl;
}

