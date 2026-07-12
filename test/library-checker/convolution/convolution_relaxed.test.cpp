#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
template<class T> using V = vector<T>;
#define REP(i, n) for (ll i = 0; i < ll(n); i++)


#include "src/number-theory/modint.hpp"
#include "src/fps/nft.hpp"
#include "src/fps/relaxed_convolution.hpp"
using Mint = ModInt<998244353>;

int N,M;
vector<Mint> A,B;

pair<Mint,Mint> f(int i,Mint c){
  Mint a=0,b=0;
  if(i<N)a=A[i];
  if(i<M)b=B[i];
  return {a,b};
}
int main() {
  cin.tie(0)->sync_with_stdio(0);
  
  cin >> N>>M;
  A=vector<Mint>(N);
  B=vector<Mint>(M);
  for(int i=0; i<N; i++){
    int c;cin>>c;
    A[i]=Mint(c);
  }
  for(int i=0; i<M; i++){
    int c;cin>>c;
    B[i]=Mint(c);
  }
  vector<Mint> C=relaxed_convolution<Mint>(N+M-1,f);
  for(int i=0;i<C.size();i++){
    cout<<C[i];
    if(i<C.size()-1){
      cout<<" ";
    }
  }
  cout<<endl;
  return 0;
}
