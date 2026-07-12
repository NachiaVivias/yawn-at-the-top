#define PROBLEM "https://judge.yosupo.jp/problem/min_plus_convolution_concave_arbitrary"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
template <class T> using V = vector<T>;
#define REP(i, n) for (ll i = 0; i < ll(n); i++)

#include "src/structure/li-chao-tree.hpp"

std::vector<int> MinPlusConvolution_AIsConcave(std::vector<int> A, std::vector<int> B){
    using namespace std;
    int N = (int)A.size();
    int M = (int)B.size();
    long long INF = 1001001001001;
    std::vector<int> C(N+M-1, 2002002002);
    for(int s=0; s<M; s+=N+1){
        int n = (M-s <= N) ? M-s : (N+1);
        auto ds1 = LiChaoTreeFlexible(N, 0,
            [&](int a, int b) -> long long {
                if(b < a) return -INF - a;
                return A[b-a] + B[s+a];
            });
        for(int i=0; i<N; i++){
            if(i+s<M) ds1.addLine(i);
            int k = ds1.minFunc(i);
            int fk = A[i-k] + B[s+k];
            if(fk < C[s+i]) C[s+i] = fk;
        }
        auto ds2 = LiChaoTreeFlexible(n-1, n-1,
            [&](int a, int b) -> long long {
                b += 1;
                if(a < b) return -INF + a;
                return A[N-1-(a-b)] + B[s+a];
            });
        for(int i=n-1; i>=1; i--){
            ds2.addLine(i);
            int k = ds2.minFunc(i-1);
            int p = s + (N-1) + i;
            int fk = A[p-s-k] + B[s+k];
            if(fk < C[p]) C[p] = fk;
        }
    }
    return C;
}

int main(){
    cin.tie(0)->sync_with_stdio(0);

    int N, M; cin >> N >> M;
    std::vector<int> A(N), B(M);
    for(auto& a : A) cin >> a;
    for(auto& b : B) cin >> b;
    auto C = MinPlusConvolution_AIsConcave(std::move(A), std::move(B));
    for(int i=0; i<N+M-1; i++){
        if(i) cout << " ";
        cout << C[i];
    } cout << "\n";
    return 0;
}

