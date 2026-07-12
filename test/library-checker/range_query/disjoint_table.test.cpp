#define PROBLEM "https://judge.yosupo.jp/problem/static_range_sum"

#include "src/common/template.hpp"
#include "src/structure/disjoint_table.hpp"

long long op(long long l, long long r){ return l+r; }
long long e(){ return 0; }

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int N, Q; cin >> N >> Q;
    vector<long long> A(N);
    for(auto& a : A) cin >> a;

    auto ds = DisjointTable<long long, op, e>(A);
    
    while(Q--){
        int l, r; cin >> l >> r;
        cout << ds.query(l,r) << "\n";
    }

    return 0;
}
