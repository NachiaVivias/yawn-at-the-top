// competitive-verifier: STANDALONE

#define _GLIBCXX_DEBUG

#include "src/common/template.hpp"
#include "src/fps/nft.hpp"
#include "src/fps/fps_composition.hpp"
#include "src/number-theory/modint.hpp"

template <class D>
vector<D> fps_composition_naive(vector<D> f, vector<D> g, ll N) {
  auto q = vector<D>(N);
  q[0] = 1;
  vector<D> res(N);
  for(int t=0; t<N; t++){
    q.resize(N);
    for(int i=0; i<N; i++) res[i] += f[t] * q[i];
    q = multiply(q, g);
  }
  return res;
}

#include <random>
const int MD = 998244353;
mt19937_64 mt;
using Mint = ModInt<998244353, 3>;

Mint random_modint(int percent_zero){
    if(int(mt() % 100) < percent_zero) return Mint(0);
    return Mint(int(mt() % MD));
}

void test(){
  for(int n=1; n<100; n++) for(int p=0; p<2; p++){
    vector<Mint> f(n), g(n);
    for(auto& x : f) x = random_modint(p * 50);
    for(auto& x : g) x = random_modint(p * 50);
    g[0] = 0;
    auto ans1 = fps_composition_naive(f, g, n);
    auto ans2 = fps_composition(f, g, n);
    bool ok = true;
    if(ans1.size() != ans2.size()) ok = false;
    if(ok) for(int i=0; i<int(ans1.size()); i++) if(ans1[i].v != ans2[i].v) ok = false;
    if(!ok) exit(1);
  }
}


int main(){
    test();
    return 0;
}
