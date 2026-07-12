#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/5/CGL_5_B"
#define ERROR 0.000001

#include <bits/stdc++.h>
using namespace std;
template <class T>
using V = vector<T>;

#include "src/geometry/primitive.hpp"
#include "src/geometry/intersect.hpp"

struct C {
  P p;
  D r;
  C(P _p = P(), D _r = D()) : p(_p), r(_r) {
  }
};
#include "src/geometry/circum_circle.hpp"


int main() {
    int N; cin >> N;
    vector<P> A(N);
    for(auto& p : A) cin >> p.x >> p.y;
    C c = smallest_circle(A);
    cout << fixed << setprecision(20);
    cout << c.p.x << ' ' << c.p.y << ' ' << c.r << endl;
}
