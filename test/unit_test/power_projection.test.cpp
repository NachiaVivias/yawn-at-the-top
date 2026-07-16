// competitive-verifier: STANDALONE

#include "src/common/template.hpp"
#include "src/fps/nft.hpp"
#include "src/fps/fps_power_projection.hpp"
#include "src/number-theory/modint.hpp"

template <class D>
vector<D> power_projection_naive(vector<D> f, vector<D> g, ll K, ll N) {
  auto q = f;
  vector<D> res;
  for(int t=0; t<N; t++){
    q.resize(K+1);
    g.resize(K+1);
    res.push_back(q[K]);
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
  for(int k=0; k<30; k++) for(int n=0; n<30; n++) for(int p=0; p<2; p++){
    vector<Mint> f(k + 1), g(k + 1);
    for(auto& x : f) x = random_modint(p * 50);
    for(auto& x : g) x = random_modint(p * 50);
    g[0] = 0;
    auto ans1 = power_projection_naive(f, g, k, n);
    auto ans2 = power_projection(f, g, k, n);
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
