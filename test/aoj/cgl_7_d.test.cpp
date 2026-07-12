#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/7/CGL_7_D"
#define ERROR 0.000001

#include <bits/stdc++.h>
using namespace std;
template <class T>
using V = vector<T>;

#include "src/geometry/primitive.hpp"
#include "src/geometry/intersect.hpp"

using Pol = V<P>;
#include "src/geometry/circle.hpp"

int main() {
    P c; D r; cin >> c.x >> c.y >> r;
    C circle(c, r);
    int q; cin >> q;
    while(q--) {
        P p0, p1; cin >> p0.x >> p0.y >> p1.x >> p1.y;
        L l;
        assert(crossCL(circle, L(p0, p1), l) >= 1);
        if(l.s.x > l.t.x || (l.s.x == l.t.x && l.s.y > l.t.y)) swap(l.s, l.t);
        cout << fixed << setprecision(20) << l.s.x << ' ' << l.s.y << ' ' << l.t.x << ' ' << l.t.y << endl;
    }
}
