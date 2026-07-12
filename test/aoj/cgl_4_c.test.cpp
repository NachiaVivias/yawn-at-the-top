#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/4/CGL_4_C"
#define ERROR 0.00001

#include <bits/stdc++.h>
using namespace std;
template <class T>
using V = vector<T>;

#include "src/geometry/primitive.hpp"
#include "src/geometry/cross_point.hpp"
#include "src/geometry/polygon.hpp"

int main() {
    int n; cin >> n;
    Pol pol(n);
    for(auto& p : pol) cin >> p.x >> p.y;
    cout << fixed << setprecision(20);
    int q; cin >> q;
    while(q--) {
        P p0, p1; cin >> p0.x >> p0.y >> p1.x >> p1.y;
        cout << area2(convex_cut(pol, {p0, p1})) / 2. << endl;
    }
}
