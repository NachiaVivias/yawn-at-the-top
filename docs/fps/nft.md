---
title: 要素が mod 998244353 の畳み込み
documentation_of: //src/fps/nft.hpp
---

`multiply` が畳み込みである。 `a.size() >= 1 && b.size() >= 1` である場合、返る配列の長さは `a.size() + b.size() - 1` である。

`tr_multiply` は転置原理によって得られたアルゴリズムで利用するものであり、 `multiply` の転置に相当する操作である。
多点評価、 Bostan--Mori 法、 FPS 合成が代表例である。
