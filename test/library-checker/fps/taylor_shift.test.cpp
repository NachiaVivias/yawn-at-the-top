#define PROBLEM "https://judge.yosupo.jp/problem/polynomial_taylor_shift"

#define _GLIBCXX_DEBUG

#include "src/common/template.hpp"
#include "src/fps/nft.hpp"
#include "src/fps/taylor_shift.hpp"
#include "src/number-theory/modint.hpp"


int main(){
    cin.tie(0)->sync_with_stdio(0);
    using Mint = ModInt<998244353, 3>;
    int N; cin >> N;
    Mint c; cin >> c.v;
    vector<Mint> A(N);
    for(int i=0; i<N; i++) cin >> A[i].v;
    auto ans = taylor_shift(A, c);
    for(int i=0; i<N; i++) cout << ans[i].v << "\n "[i+1<N];
    return 0;
}
