#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/2/CGL_2_C"
#define ERROR 0.00000001

#include <bits/stdc++.h>
using namespace std;

#include "src/geometry/primitive.hpp"
#include "src/geometry/cross_point.hpp"

int main() {
    int q; cin >> q;
    cout << fixed << setprecision(20);
    while(q--) {
        P p0, p1, p2, p3; cin >> p0.x >> p0.y >> p1.x >> p1.y >> p2.x >> p2.y >> p3.x >> p3.y;
        P q;
        assert(crossSS(L(p0, p1), L(p2, p3), q) == 1);
        cout << q.x << " " << q.y << endl;
    }
}
