struct PalNode {
  ll len = 0, diff = 0;
  PalNode *li = 0;  // suffix link
  PalNode *par = 0; // abcba --> bcb
  PalNode *sli = 0; // series link
  PalNode *nx[26] = {};
};
V<PalNode> pool(1000000); // string length + O(1)
PalNode* poolptr = pool.data();
struct PalTree {
  using np = PalNode*;
  np n0, n1, v;
  V<int> s;
  PalTree() : n0(poolptr++), n1(poolptr++), v(n1) {
    *n0 = { -1 };
    *n1 = { 0, 1, n0 };
  }
  np add_char(int c){
    int i = s.size();
    s.push_back(c);
    if(v->len == i) v = v->li;
    while(s[i - v->len - 1] != c) v = v->li;
    if(!v->nx[c]){
      np n = poolptr++, m = v->li, l = n1;
      if(v->len >= 0){
        while(s[i - m->len - 1] != s[i]) m = m->li;
        l = m->nx[c];
      }
      v->nx[c] = n;
      *n = { v->len + 2, v->len + 2 - l->len, l, v };
      n->sli = n->diff == l->diff ? l->sli : n;
    }
    return v = v->nx[c];
  }
};