// competitive-verifier: STANDALONE

#include "src/common/template.hpp"
#include "src/number-theory/modint.hpp"
using Mint = ModInt<998244353>;
#include "src/fps/Interpolation.hpp"

using namespace std;

const int MD = 998244353;
mt19937_64 mt;

Mint random_modint(int percent_zero){
    if(int(mt() % 100) < percent_zero) return Mint(0);
    return Mint(int(mt() % MD));
}

void test_unit(int n, int m, int percent_zero){
    vector<Mint> poly(n);
    for(auto& v : poly) v = random_modint(percent_zero);
    auto eval = [&](Mint x) -> Mint {
        Mint v = 0;
        for(int i=n-1; i>=0; i--) v = v * x + poly[i];
        return v;
    };
    vector<Mint> pts;
    for(int i=0; i<m; i++){
        while(1) {
            Mint h = random_modint(0);
            int dupl = 0;
            for(auto a : pts) if(a.v == h.v) dupl = 1;
            if(!dupl) {
                pts.push_back(h);
                break;
            }
        }
    }
    vector<Mint> y;
    for(auto x : pts) y.push_back(eval(x));
    Mint x0 = random_modint(0);
    Mint fx0 = Interpolation(m, pts, y, x0.v);
    if(eval(x0).v != fx0.v) exit(1);
}

void test(){
    for(int p : {0,50})
    for(int n=1; n<20; n++)
    for(int m=n; m<20; m++)
    for(int i=0; i<100; i++)
        test_unit(n, m, p);
}


int main(){
    test();
    return 0;
}

