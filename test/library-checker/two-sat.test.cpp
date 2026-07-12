#define PROBLEM "https://judge.yosupo.jp/problem/two_sat"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
template <class T>
using V = vector<T>;
#define REP(i, n) for (ll i=0; i<ll(n); i++)
template<class A, class B>
bool chmax(A &a, B b) { return a < b && (a = b, true); }
template<class A, class B>
bool chmin(A &a, B b) { return b < a && (a = b, true); }
#include "src/graph/scc.hpp"
#include "src/graph/two-sat.hpp"


int main(){
    cin.tie(0)->sync_with_stdio(0);
    string tmp;
    int n,m; cin >> tmp >> tmp >> n >> m;
    TwoSat ts(n+1);
    REP(i,m){
        int a,b; cin >> a >> b >> tmp;
        ts.either(abs(a), a>0, abs(b), b>0);
    }
    if(!ts.solve()){
        cout << "s UNSATISFIABLE\n";
        return 0;
    }
    cout << "s SATISFIABLE\nv ";
    auto res=ts.res;
    REP(i,n){
        if(res[i+1]) cout<< (i+1) << ' ';
        else cout << -(i+1) << ' ';
    }
    cout << "0\n";
    return 0;
}
