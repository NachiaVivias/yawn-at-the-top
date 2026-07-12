#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/2/ITP1/1/ITP1_1_A"
#include "unit_test_module.hpp"
#include "src/common/template.hpp"
#include "src/number-theory/min_of_mod_of_linear.hpp"


std::vector<long long> solve(long long m, long long a, long long b){
  auto ex = MinModLinear(m, a, b);
  std::vector<long long> res;
  for(auto q : ex) for(long long i=0; i<q.len; i++) res.push_back(q.lx + i * q.p);
  return res;
}

std::vector<long long> naive(long long m, long long a, long long b){
  long long v = m;
  std::vector<long long> res;
  for(long long i=0; i<m; i++){
    long long q = (a * i + b) % m;
    if(q < v){ res.push_back(i); v = q; }
  }
  return res;
}

void test(){
  for(long long m=1; m<=100; m++)
  for(long long a=0; a<m; a++)
  for(long long b=0; b<m; b++){
    auto ans1 = solve(m, a, b);
    auto ans2 = naive(m, a, b);
    if(ans1 != ans2){
      exit(1);
    }
  }
}
