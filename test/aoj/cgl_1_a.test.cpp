#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/1/CGL_1_A"
#define ERROR 0.00000001

#include <bits/stdc++.h>
using namespace std;

#include "src/geometry/primitive.hpp"
#include "src/geometry/intersect.hpp"

int main() {
    P p1, p2; cin >> p1.x >> p1.y >> p2.x >> p2.y;
    L l(p1, p2);
    int Q; cin >> Q;
    cout << fixed << setprecision(20);
    while(Q--) {
        P p; cin >> p.x >> p.y;
        P q = project(l, p);
        cout << q.x << ' ' << q.y << endl;
    }
}
