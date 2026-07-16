// competitive-verifier: STANDALONE

#include "src/common/template.hpp"
#include "src/number-theory/nimber_product.hpp"


#include <random>
mt19937_64 mt;

void test(){
  NimberManager nim;
  int T = 400000;
  for(int ti=0; ti<T; ti++){
    unsigned long long x = mt();
    unsigned long long y = nim.inv(x);
    if(nim.mul(x, y) != 1){
      exit(1);
    }
  }
}


int main(){
    test();
    return 0;
}
