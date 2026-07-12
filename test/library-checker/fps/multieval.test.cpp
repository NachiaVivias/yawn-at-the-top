#define PROBLEM "https://judge.yosupo.jp/problem/multipoint_evaluation"
#include "src/common/template.hpp"
#include "src/fps/nft.hpp"
#include "src/fps/fps.hpp"
#include "src/fps/multieval.hpp"
#include "src/number-theory/modint.hpp"


int main(){
    cin.tie(0)->sync_with_stdio(0);
    using Mint = ModInt<998244353, 3>;
    
    int N; cin >> N;
    int M; cin >> M;
    vector<Mint> C(N), P(M);
    for(int i=0; i<N; i++) cin >> C[i].v;
    for(int i=0; i<M; i++) cin >> P[i].v;

    auto me = MultiEval(P); // eval points
    auto ans = me.query(C); // polynomial

    for(int i=0; i<M; i++) cout << ans[i].v << "\n "[i+1<M];
    return 0;
}
