#define PROBLEM "https://judge.yosupo.jp/problem/sum_of_floor_of_linear"

#define _GLIBCXX_DEBUG

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#include "src/number-theory/floor-sum.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    
    int t; cin >> t;
    while(t--) {
        long long n, m, a, b; cin >> n >> m >> a >> b;
        cout << gauss_sum(n, a, b, m) << '\n';
    }
}
