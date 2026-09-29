#define PROBLEM "https://judge.yosupo.jp/problem/lca"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = 1ll << 60;
#define REP(i, n) for (ll i=0; i<ll(n); i++)
template <class T> using V = vector<T>;

#include "src/tree/hld.hpp"




pair<vector<int>, vector<int>> get_random_permutation(int N){
    mt19937_64 mt(time(nullptr));
    vector<int> perm(N), iperm(N);
    for(int i=0; i<N; i++) perm[i] = i;
    for(int i=1; i<N; i++) swap(perm[mt() % i], perm[i]);
    for(int i=0; i<N; i++) iperm[perm[i]] = i;
    return {perm, iperm};
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    
    int N; cin >> N;
    int Q; cin >> Q;

    auto [perm, iperm] = get_random_permutation(N);

    vector<vector<int>> t(N);
    for(int i=1; i<N; i++){
        int p; cin >> p;
        t[perm[p]].push_back(perm[i]);
        t[perm[i]].push_back(perm[p]);
    }

    auto hld = HLD(N, t, perm[0]);

    for(int i=0; i<Q; i++){
        int u,v; cin >> u >> v;
        u = perm[u];
        v = perm[v];
        cout << iperm[hld.lca(u,v)] << "\n";
    }

    return 0;
}
