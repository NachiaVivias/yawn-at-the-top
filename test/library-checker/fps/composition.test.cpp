#define PROBLEM "https://judge.yosupo.jp/problem/composition_of_formal_power_series_large"
#include "src/common/template.hpp"
#include "src/fps/nft.hpp"
#include "src/fps/fps_composition.hpp"
#include "src/number-theory/modint.hpp"


int main(){
    cin.tie(0)->sync_with_stdio(0);
    using Mint = ModInt<998244353, 3>;

    int N; cin >> N;
    vector<Mint> F(N), G(N);
    for(int i=0; i<N; i++) cin >> F[i].v;
    for(int i=0; i<N; i++) cin >> G[i].v;

    auto ans = fps_composition(F, G, N);

    for(int i=0; i<N; i++) cout << ans[i].v << "\n "[i+1<N];

    return 0;
}
