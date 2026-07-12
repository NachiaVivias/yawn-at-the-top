#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

// std::setの上位互換
tree<int, null_type, less<int>, rb_tree_tag,
     tree_order_statistics_node_update>
    s;
s.find_by_order(k);  // k番目の要素のイテレータ
s.order_of_key(k);   // k未満が何個あるか

// std::unordered_mapの上位互換(4倍くらい早いらしい)
// 第3template引数にハッシュ関数指定可能
gp_hash_table<int, int> m;

// ==============

#include <ext/rope>
using namespace __gnu_cxx;

// 計算量不明
rope<int> v0, v1, v2;
v0.insert(0, v1);     // 0番目にv1を挿入
v0.insert(0, 1);      // 0番目に1を挿入
v0.replace(0, 2, 1);  // 0番目から2要素を1つの1に変更
v0.replace(0, 2, v1);  // 0番目の2要素をv1に変更
v0.erase(0, 2);        // 0番目から2要素を削除
// replaceやeraseは2つのイテレータで範囲指定もできる
v2 = v0.substr(0, 2);  // 0番目から2要素で1つのropeに
v0.mutable_begin(), v0.mutable_end();
// 変更可能な両端イテレータ
v0[2];  // 2番目の要素
// resize, reserveはvectorと同じ
