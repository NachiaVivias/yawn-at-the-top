// number-theory/modint.hpp , 同/crt.hpp (inv_mod まで) ,
// 同/garner.hpp , fps/nft.hpp
template <int MOD, int g>
V<int> multiply_mod(const V<int>& a, const V<int>& b) {
  V<ModInt<MOD, g>> c, d;
  for(auto x : a) c.push_back(x);
  for(auto x : b) d.push_back(x);
  c = multiply(c, d);
  V<int> res;
  for(auto x : c) res.push_back(x.v);
  return res;
}
template<class mint>
V<mint> multiply_garner(V<mint> a, V<mint> b){
    constexpr int m[] = {
        167772161, 469762049, 754974721 };
    auto g = garner<mint>(V<ll>(m, m+3));
    V<int> c(a.size()), d(b.size());
    REP(i,a.size()) c[i] = a[i].v;
    REP(i,b.size()) d[i] = b[i].v;
    V<V<int>> res(3);
    res[0] = multiply_mod<m[0], 3>(c, d);
    res[1] = multiply_mod<m[1], 3>(c, d);
    res[2] = multiply_mod<m[2], 11>(c, d);
    V<ll> r(3);
    V<mint> ans(res[0].size());
    REP(i,res[0].size()){
        REP(j,3) r[j] = res[j][i];
        ans[i] = g(r);
    }
    return ans;
}