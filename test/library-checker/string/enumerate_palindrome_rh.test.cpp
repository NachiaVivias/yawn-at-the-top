#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_palindromes"

#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;

#include "src/string/rolling-hash.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    
    string s; cin >> s;
    string rs(s.rbegin(), s.rend());
    RollingHash rh;
    auto hs = rh.build(s);
    auto rhs = rh.build(rs);
    vector<int> ans;
    for(int i = 0; i < ssize(s); i++) {
        if(i != 0) {
            int ok = 0, ng = min(i, (int)ssize(s)-i)+1;
            while(ng - ok > 1) {
                int mid = midpoint(ok, ng);
                if(rh.query(hs, i-mid, i+mid) == rh.query(rhs, ssize(s)-i-mid, ssize(s)-i+mid)) ok = mid;
                else ng = mid;
            }
            cout << ok*2 << ' ';
        }
        {
            int ok = 0, ng = min(i, (int)ssize(s)-i-1)+1;
            while(ng - ok > 1) {
                int mid = midpoint(ok, ng);
                if(rh.query(hs, i-mid, i+mid+1) == rh.query(rhs, ssize(s)-i-mid-1, ssize(s)-i+mid)) ok = mid;
                else ng = mid;
            }
            cout << ok*2+1 << (i == ssize(s)-1 ? '\n' : ' ');
        }
    }
}
