---
title: クエリの単調性を利用して deque で処理する CHT
documentation_of: //src/convex/cht_monotone.hpp
---


```c++
template<class Pos, class F>
struct CHTMonotone {
  struct Q { Pos l, r; F f; };
  deque<Q> a;
  CHTMonotone(Pos l, Pos r, F inf);
  void add(F f, auto fx, auto cross);
  F query(Pos x);
  F query_inc(Pos x);
  F query_dec(Pos x);
};
```

* `Pos` : CHT の $x$ 軸の座標の型。
* `F` : CHT における直線の型。
* `Q::l` , `Q::r` : 関数 `Q::f` が最小値をとるような $x$ 座標を閉区間 $[l,r]$ で表す。
* `a` : 現在の最小値を表す折れ線。 $x$ 座標の昇順で管理されている。
* コンストラクタ : 計算範囲を $l \leq x \leq r$ に制約する。 `cross` は各 $x$ での INF として機能する。
* `add` : 関数 `f` を追加する。この時点で `f` が最小値をとる区間が、 $l \leq x \leq r$ と左端または右端のどちらかを共有する区間でなければならない。（例えば、関数が一次関数で、傾きの昇順で追加すると、左端が必ず一致するので OK 。）
    * `fx` : `Val fx(F f, Pos x)` で $f(x)$ が計算され、結果の `Val` 型変数を比較できなければならない。
    * `cross` : `void cross(F a, F b, Pos& xa, Pos& xb)` で呼び出される。 $x _ a \leq x _ b$ で、 $x=x _ a$ では $a(x)$ のほうが、 $x = x _ b$ で $b(x)$ のほうが小さいということを仮定して、 $x _ a$ , $x _ b$ をそれぞれ次の値に変更しなければならない。
        * $x _ a$ : $x _ a \leq x \leq x _ b$ であって、 $a(x) \leq b(x)$ となるような $x$
        * $x _ b$ : $x _ a \leq x \leq x _ b$ であって、 $b(x) \leq a(x)$ となるような $x$
        * $[x _ a, x]$ と $[x, x _ b]$ で $[x _ a, x _ b]$ がカバーされる。
* `query` : 与えた $x$ での最小値を求める。
* `query_inc` : 与えた $x$ で最小値を求め、計算範囲の下限を $x$ に変更する。

## 使い方

### Pos が整数型

多少気持ち悪い関数でも、二分探索で `cross` を実装できる。

```c++
void cross(F a, F b, ll& xa, ll& xb){
  while(abs(xa - xb) > 1){
    Pos x = xa + (xb - xa) / 2;
    (a(x) < b(x) ? xa : xb) = x;
  }
}
```

### Pos が実数型

二分探索は比較的安全だが、収束が遅い。
事故の心配がなければ直線の交点を計算するのが速い。

```c++
void cross(F a, F b, double& xa, double& xb){
  xa = xb = -(a.b - b.b) / (a.a - b.a);
}
```

## LARSCH の代用

Monge 性で高速化する DP に利用できる。オンライン行最小値問題は、 CHT を使うと $O(N \log N)$ で解ける。（ LARSCH だと $O(N)$ ）
