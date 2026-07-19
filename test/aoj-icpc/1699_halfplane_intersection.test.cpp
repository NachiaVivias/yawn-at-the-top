#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/challenges/sources/ICPC/Prelim/1699"
#define ERROR 0.000001

// maybe slows down std::sort
// #define _GLIBCXX_DEBUG

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = 1ll << 60;
#define REP(i,n) for(ll i=0; i<ll(n); i++)
template<class T>
using V = vector<T>;
template<class A, class B>
bool chmax(A &a, B b){ return a < b && (a = b, true); }
template<class A, class B>
bool chmin(A &a, B b){ return b < a && (a = b, true); }

#include "src/geometry/primitive.hpp"
#include "src/geometry/halfplane_intersection.hpp"

void testcase(){
    ll N, M; cin >> N >> M;
    if(N == 0) exit(0);
    V<P> A(N), B(M);
    REP(i,N){ ll x, y; cin >> x >> y; A[i] = {D(x),D(y)}; }
    REP(i,M){ ll x, y; cin >> x >> y; B[i] = {D(x),D(y)}; }
    
    D ok = 0, ng = 1.0e6;
    REP(t,60){
        D X = (ok + ng) / 2.0;
        auto xB = B;
        for(auto& b : xB) b *= X;
        V<L> lns;
        REP(i,N){
            L l = L(A[i], A[(i+1)%N]);
            D mxx = -1.0e100;
            ll mxj = 0;
            REP(j,M){
                D f = -crs(l.vec(), xB[j]);
                if(mxx < f){ mxx = f; mxj = j; }
            }
            lns.push_back(L(l.s - xB[mxj], l.t - xB[mxj]));
        }
        if(halfplane_intersection(lns).empty()) ng = X; else ok = X;
    }
    cout << ok << "\n";
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cout.precision(20); cout << fixed;
    while(1)
        testcase();
    return 0;
}
