/// BEGIN https://github.com/NachiaVivias/yawn-at-the-top/blob/main/test/library-checker/unionfind.test.cpp
#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"

#define _GLIBCXX_DEBUG

#include <bits/stdc++.h>
using namespace std;
template <class T> using V = vector<T>;
using ll = long long;
#define REP(i,n) for(ll i=0; i<ll(n); i++)

#include "src/structure/unionfind.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int N, Q; cin >> N >> Q;

    auto dsu = UnionFind(N);
    
    for(int i=0; i<Q; i++){
        int t, u, v; cin >> t >> u >> v;
        if(t == 0){
            dsu.merge(u, v);
        } else {
            if(dsu.same(u, v)){
                cout << "1\n";
            } else {
                cout << "0\n";
            }
        }
    }

    return 0;
}
/// END https://github.com/NachiaVivias/yawn-at-the-top/blob/main/test/library-checker/unionfind.test.cpp
