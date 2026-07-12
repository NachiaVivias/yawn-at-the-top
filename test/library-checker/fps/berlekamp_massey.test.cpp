#define PROBLEM "https://judge.yosupo.jp/problem/find_linear_recurrence"
#include "src/common/template.hpp"
#include "src/fps/nft.hpp"
#include "src/fps/berlekamp_massey.hpp"
#include "src/number-theory/modint.hpp"


int main(){
    cin.tie(0)->sync_with_stdio(0);
    using Mint = ModInt<998244353, 3>;

    int N; cin >> N;
    vector<Mint> A(N);
    for(int i=0; i<N; i++) cin >> A[i].v;
    
    auto ans = berlekamp_massey(A);
    cout << (ans.size() - 1) << "\n";
    for(int i=1; i<int(ans.size()); i++){
        if(i != 1) cout << " ";
        cout << (-ans[i]).v;
    } cout << "\n";

    return 0;
}

