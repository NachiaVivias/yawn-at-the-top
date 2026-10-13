---
title: 要素が任意 modの畳み込み
documentation_of: //src/fps/garner_convolution.hpp
---

畳み込みを利用する他のライブラリが `multiply` のみを利用している場合、 `multiply` に代わりに `multiply_garner` に差し替えることで mod 998244353 以外の畳み込みを用いたアルゴリズムを利用できる。
