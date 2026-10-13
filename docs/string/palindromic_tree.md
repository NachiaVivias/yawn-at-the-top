---
title: 回文木
documentation_of: //src/string/palindromic_tree.hpp
---

### series link

suffix link を、 `len` が等差数列である区間を series として、 series の端までジャンプするようなリンク。

```
    2       5       5       5       11      11      11
()<-----()<-----()<-----()<-----()<-----()<-----()<-----() suffix link
        ^ |     ^ |       |       |     ^ |       |       |
         -      |-        |       |     |-        |       |  series link
                |---------        |     |---------        |
                 -----------------       ----------------- 
```

以下の形のループで、文字列 $S$ を空でない回文部分文字列に分割する DP の遷移を過不足なく管理しやすいことが知られている。

```c++
for(auto w = v; w && w->len >= 1; w = w->sli->li)
    // w --~--> (w->sli)  is a series
```

### 例題

長さ $N$ の英小文字列 $S$ が与えられる。これを空でない回文部分文字列に分割する方法の個数を求めよ。

```c++
struct PalNode {
  ll len = 0, diff = 0;
  PalNode *li = 0;  // suffix link
  PalNode *par = 0; // abcba --> bcb
  PalNode *sli = 0; // series link
  PalNode *nx[26] = {};
  Mint dp;
};

// ...

void solve(ll N, string S){
    ll N; cin >> N;
    string S; cin >> S;

    V<ll> dp(N+1); dp[0] = 1;
    PalTree pt;
    REP(i,N){
        ll c = S[i] - 'a';
        auto v = pt.add_char(c);
        for(auto w = v; w && w->len >= 1; w = w->sli->li){
            w->dp = dp[i+1-w->sli->len];
            if(w != w->sli) w->dp += w->li->dp;
            dp[i+1] += w->dp;
        }
    }
    cout << dp[N] << "\n";
}
```

verify: ShareOJ(β) https://www.share-oj.net/problems/3024115d-1a55-4bcb-b67b-d0ac823c03e3
