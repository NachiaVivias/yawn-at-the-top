---
title: direct link 搭載 Aho-Corasick 法
documentation_of: //src/string/aho-corasick-direct-link.hpp
---


Aho-Corasick 法のオートマトンを作ったのち、各ノード v と各文字 c について、 v から文字 c を追加したときに遷移する先を計算しておく。

DFA になるので、文字列を数え上げる DP とかができる。


文字列検索

* https://atcoder.jp/contests/abc362/submissions/77257059

DP:

* https://onlinejudge.u-aizu.ac.jp/challenges/sources/ICPC/Regional/1421
