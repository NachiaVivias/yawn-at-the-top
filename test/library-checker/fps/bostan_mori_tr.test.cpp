#define PROBLEM "https://judge.yosupo.jp/problem/consecutive_terms_of_linear_recurrent_sequence"

#define _GLIBCXX_DEBUG

#include "src/common/template.hpp"
#include "src/fps/nft.hpp"
#include "src/fps/bostan_mori_msb_first.hpp"
#include "src/number-theory/modint.hpp"


int main(){
  cin.tie(0)->sync_with_stdio(0);
  using Mint = ModInt<998244353, 3>;
    
  long long D, K, M; cin >> D >> K >> M;
  vector<Mint> a(D);
  for(long long i=0; i<D; i++) cin >> a[i].v;
  vector<Mint> c(D + 1, 1);
  for(long long i=1; i<=D; i++){ cin >> c[i].v; c[i] = -c[i]; }
  a = multiply(a, c);
  a.resize(D);
  a.push_back(0);
  auto ans = bostan_mori(a, c, K, M);

  M = ans.size();
  for(long long i=0; i<M; i++) cout << ans[i].v << "\n "[i+1<M];
  return 0;
}
