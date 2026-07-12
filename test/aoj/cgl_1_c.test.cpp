#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/1/CGL_1_C"

#include <bits/stdc++.h>
using namespace std;

#include "src/geometry/primitive.hpp"

int main() {
    P p1, p2;
    cin >> p1.x >> p1.y >> p2.x >> p2.y;
    int q; cin >> q;
    while(q--) {
        P p; cin >> p.x >> p.y;
        int c = ccw(p1, p2, p);
        if(c==-2) cout << "ONLINE_FRONT\n";
        if(c==-1) cout << "CLOCKWISE\n";
        if(c==0) cout << "ON_SEGMENT\n";
        if(c==1) cout << "COUNTER_CLOCKWISE\n";
        if(c==2) cout << "ONLINE_BACK\n";
    }
}
