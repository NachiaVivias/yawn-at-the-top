#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/7/CGL_7_H"
#define ERROR 0.00001

#include <bits/stdc++.h>
using namespace std;
template <class T>
using V = vector<T>;

#include "src/geometry/primitive.hpp"
#include "src/geometry/intersect.hpp"

using Pol = V<P>;
#include "src/geometry/circle.hpp"

int main() {
    int n; D r; cin >> n >> r;
    C c(P(0, 0), r);
    Pol pol(n);
    for(auto& p : pol) cin >> p.x >> p.y;
    cout << fixed << setprecision(20);
    cout << area2CPol(c, pol) / 2. << endl;
}
