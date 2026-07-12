#define PROBLEM "https://judge.yosupo.jp/problem/runenumerate"

#include "src/common/template.hpp"
#include "src/string/z_algorithm_iter.hpp"
#include "src/string/run_enum.hpp"


int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    std::string S; std::cin >> S;
    auto res = EnumerateRuns(S);

    if (!res.empty()){
        using T = tuple<int,int,int>;
        auto ord1 = [](Run l, Run r) {
        return T(l.p, l.l, l.r) < T(r.p, r.l, r.r);
        };
        auto ord2 = [](Run l, Run r) {
        return T(l.l, l.r, l.p) < T(r.l, r.r, r.p);
        };
        int p = 0;
        sort(res.begin(), res.end(), ord2);
        for(int i=0; i<int(res.size()); i++) if(i) {
        if (res[p].l == res[i].l && res[p].r == res[i].r && res[p].p == res[i].p){
            exit(0); // 重複
        }
        if (res[p].l != res[i].l || res[p].r != res[i].r)
            res[++p] = res[i];
        }
        res.resize(p + 1);
        sort(res.begin(), res.end(), ord1);
    }

    cout << res.size() << "\n";
    for(auto run : res) cout << run.p << ' ' << run.l << ' ' << run.r << '\n';
    return 0;
}
