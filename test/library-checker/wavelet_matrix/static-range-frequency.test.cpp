#define PROBLEM "https://judge.yosupo.jp/problem/static_range_frequency"

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
        int l, r, x; cin >> l >> r >> x;
        cout << mat.range_freq(l, r, x+1) - mat.range_freq(l, r, x) << '\n';
    }
}


