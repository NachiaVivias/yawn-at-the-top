/// Original: Gifted Infants(AhoCorasick) https://yosupo.hatenablog.com/entry/2019/07/02/122433
struct ACTrie {
  using NP = ACTrie*;
  V<int> acc;
  map<int, NP> next;
  NP fail = 0, dnx = 0;
 private:
  void add(const string& s, int id, int p = 0) {
    if (p == int(s.size())) {
      acc.push_back(id);
      return;
    }
    if (!next[s[p]]) next[s[p]] = new ACTrie();
    next[s[p]]->add(s, id, p + 1);
  }
  template <class OP>
  NP count(OP op, int p) {
    if (!fail) return this;
    for (int id : acc) op(id, p);
    if (dnx) {
      dnx->count(op, p);
    } else {
      dnx = fail->count(op, p);
    }
    return acc.size() ? this : dnx;
  }
 public:
  // パターンにマッチするたびにop(string ID,
  // 発見位置の終端)を呼び出す
  // 終端が同じで複数マッチする文字列が存在する場合，⻑い順に呼び出される
  // s = "abaaba", pattern = {"ab", "ba"} なら
  // op(0, 2), op(1, 3), op(0, 5), op(1, 6)
  template <class OP>
  void match(const string& s, OP op, int p = 0) {
    if (p == int(s.size())) return;
    if (next[s[p]]) {
      next[s[p]]->count(op, p + 1);
      next[s[p]]->match(s, op, p + 1);
    } else {
      if (!fail)
        match(s, op, p + 1);  // root
      else
        fail->match(s, op, p);  // other
    }
  }
  static NP make(V<string> v) {
    NP tr = new ACTrie();
    for (int i = 0; i < int(v.size()); i++) {
      tr->add(v[i], i);
    }
    V<NP> q = {tr};
    tr->fail = 0;
    for(size_t qi = 0; qi < q.size(); qi++){
      NP ntr = q[qi];
      for (auto [i, to] : ntr->next) {
        NP f = ntr->fail;
        while (f && !f->next.count(i)) f = f->fail;
        to->fail = f ? f->next[i] : tr;
        q.push_back(to);
      }
    }
    return tr;
  }
};
