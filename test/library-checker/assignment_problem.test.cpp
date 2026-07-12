#define PROBLEM "https://judge.yosupo.jp/problem/assignment"

#include <bits/stdc++.h>
using namespace std;
template <class T> using V = vector<T>;
using ll = long long;
#define REP(i,n) for(ll i=0; i<ll(n); i++)

#include "src/graph/assignment_problem.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    
    int n; cin >> n;
    vector<vector<long long>> A(n,vector<long long>(n));
    for(auto& a : A) for(auto& b : a) cin >> b;

    auto ans = AssignmentProblem(n, n, A, n, 1ll << 60);

    long long sum = 0;
    for(int i=0; i<n; i++) sum += A[i][ans[i]];

    cout << sum << "\n";
    for(int i=0; i<n; i++){
        if(i) cout << " ";
        cout << ans[i];
    } cout << "\n";

    return 0;
}
