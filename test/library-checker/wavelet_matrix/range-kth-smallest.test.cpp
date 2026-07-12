#define PROBLEM "https://judge.yosupo.jp/problem/range_kth_smallest"

#include "src/common/template.hpp"
#include "src/structure/wavelet_matrix.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    
    int n, q; cin >> n >> q;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    WaveletMatrix<int, 31> mat(a);
    while(q--) {
        int l, r, k; cin >> l >> r >> k;
        cout << mat.kth_smallest(l, r, k) << '\n';
    }
}

