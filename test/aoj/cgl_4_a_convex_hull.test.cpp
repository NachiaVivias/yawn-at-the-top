#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/4/CGL_4_A"

#include <bits/stdc++.h>
using namespace std;
template <class T>
using V = vector<T>;

#include "src/geometry/primitive.hpp"
#include "src/geometry/convex_hull.hpp"


int main() {
    int n; cin >> n;
    vector<P> pol(n);
    for(auto& p : pol) cin >> p.x >> p.y;
    auto hull = convex(pol, 1);
    auto it = min_element(hull.begin(), hull.end(), [](const P& a, const P& b) {
        return a.y == b.y ? a.x < b.x : a.y < b.y;
    });
    rotate(hull.begin(), it, hull.end());
    cout << hull.size() << endl;
    for(const auto& p : hull) cout << p.x << ' ' << p.y << endl;
}
