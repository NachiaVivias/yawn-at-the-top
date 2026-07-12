#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/7/CGL_7_E"
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
    P c1; D r1; cin >> c1.x >> c1.y >> r1;
    C circle1(c1, r1);
    P c2; D r2; cin >> c2.x >> c2.y >> r2;
    C circle2(c2, r2);
    cout << fixed << setprecision(20);
    D l, r;
    assert(crossCC(circle1, circle2, l, r) >= 1);
    P p1 = circle1.p + P::polar(circle1.r, l), p2 = circle1.p + P::polar(circle1.r, r);
    if(p1.x > p2.x) swap(p1, p2);
    if(p1.x == p2.x && p1.y > p2.y) swap(p1, p2);
    cout << p1.x << " " << p1.y << " " << p2.x << " " << p2.y << endl;
}

