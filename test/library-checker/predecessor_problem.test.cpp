#define PROBLEM "https://judge.yosupo.jp/problem/predecessor_problem"

#define _GLIBCXX_DEBUG

#include <bits/stdc++.h>
using namespace std;
template <typename T>
using V = vector<T>;
#include "src/structure/segtree.hpp"

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, q; cin >> n >> q;
    string t; cin >> t;
    vector<int> iv(n);
    for(int i = 0; i < n; i++) iv[i] = t[i]-'0';
    Segtree<int, [](int x, int y) { return max(x, y); }> seg(iv, 0);
    while(q--) {
        int op, k; cin >> op >> k;
        if(op == 0) seg.set(k, 1);
        else if(op == 1) seg.set(k, 0);
        else if(op == 2) cout << seg.get(k) << '\n';
        else if(op == 3) {
            int ans = seg.max_right(k, [&](int v) { return v == 0; });
            if(ans == n) ans = -1;
            cout << ans << '\n';
        } else {
            int ans = seg.min_left(k+1, [&](int v) { return v == 0; }) - 1;
            cout << ans << '\n';
        }
    }
}
