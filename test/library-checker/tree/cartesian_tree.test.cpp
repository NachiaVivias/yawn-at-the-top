#define PROBLEM "https://judge.yosupo.jp/problem/cartesian_tree"

#include "src/common/template.hpp"
#include "src/structure/cartesian_tree.hpp"

#define _GLIBCXX_DEBUG

int main(){
  cin.tie(0)->sync_with_stdio(0);
  
  int N; cin >> N;
  std::vector<int> A(N);
  for(auto& a : A) cin >> a;

  auto tr = cartesian_tree(A);
  for(int i=0; i<N; i++){
    if(tr[i] == -1) tr[i] = i;
    if(i) cout << " ";
    cout << tr[i];
  } cout << "\n";

  return 0;
}
