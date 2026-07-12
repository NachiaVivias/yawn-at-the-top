#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/3/CGL_3_C"

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
    int q; cin >> q;
    while(q--) {
        P p; cin >> p.x >> p.y;
        cout << contains(pol, p) << endl;
    }
}
