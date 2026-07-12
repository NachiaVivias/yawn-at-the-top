#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/4/CGL_4_B"
#define ERROR 0.000001

#include <bits/stdc++.h>
using namespace std;
template <class T>
using V = vector<T>;

#include "src/geometry/primitive.hpp"
#include "src/geometry/intersect.hpp"
#include "src/geometry/convex_polygon_diameter.hpp"


int main() {
    int n; cin >> n;
    V<P> pol(n);
    for(auto& p : pol) cin >> p.x >> p.y;
    cout << fixed << setprecision(20);
    cout << diameter(pol) << endl;;
}
