/// Original: ei1333 https://ei1333.github.io/library/graph/mst/directed-mst.hpp
template <typename T, bool isMin = true>
struct LeftistHeap {
  struct Node {
    T key, lazy;
    Node *l, *r;
    int s;
    int idx;
    Node(T key, int idx)
        : key(key), lazy(0), l(0), r(0), s(1), idx(idx) {}
  };
  using np = Node*;
  np alloc(T key, int idx) {
    return new Node(key, idx);
  }
  np add(np t, T z) {
    if (t) t->lazy += z, t->key += z;
    return t;
  }
  np prop(np t) {
    t->l = add(t->l, t->lazy);
    t->r = add(t->r, t->lazy);
    t->lazy = 0;
    return t;
  }
  np meld(np a, np b) {
    if (!a || !b) return a ? a : b;
    a = prop(a), b = prop(b);
    if ((a->key < b->key) ^ isMin) swap(a, b);
    a->r = meld(a->r, b);
    if (!a->l || a->l->s < a->r->s) swap(a->l, a->r);
    a->s = (a->r ? a->r->s : 0) + 1;
    return a;
  }
  np pop(np t) {
    return meld(t->l, t->r);
  }
};

struct Edge {
  using Cost = ll;
  int from, to;
  Cost cost;
};
// root -----> leaf
// from -----> to
// ans[root] = -1; ans[v] = (? --> v) なる辺番号
V<int> directed_mst(int n, int root, V<Edge> E) {
  REP(i, n) if (i != root) E.push_back({ (int)i, root, 0 });
  int x = 0;
  V<int> par(2 * n, -1), vis(par), uf(par), st;
  using Heap = LeftistHeap<Edge::Cost, 1>;
  Heap h;
  V<typename Heap::np> ins(2 * n, 0);
  REP(i, E.size()) ins[E[i].to] = h.meld(ins[E[i].to], h.alloc(E[i].cost, i));
  auto Find = [&](auto& f, int a) -> int {
    return uf[a] < 0 ? a : (uf[a] = f(f, uf[a]));
  };
  auto go = [&](int v) {
    return Find(Find, E[ins[v]->idx].from);
  };
  for (int i = n; ins[x]; i++) {
    for (; vis[x] == -1; x = go(x)) vis[x] = 0;
    for (; x != i; x = go(x)) {
      auto w = ins[x]->key;
      ins[i] = h.meld(ins[i], h.add(h.pop(ins[x]), -w));
      uf[x] = par[x] = i;
    }
    for (; ins[x] && go(x) == x; ins[x] = h.pop(ins[x]));
  }
  V<int> ans(n, -1);
  for (int i = root; i != -1; i = par[i]) vis[i] = 1;
  do {
    if(vis[x] != 1){
      int e = ins[x]->idx;
      ans[E[e].to] = e;
      for (int j = E[e].to; j != -1 && !vis[j]; j = par[j])
        vis[j] = 1;
    }
  } while(x--);
  return ans;
}