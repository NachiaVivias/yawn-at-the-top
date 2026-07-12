// F : S rake(S l, S r);
// G : S extend(S a, int old_root, int new_root)
template<class S, class F, class G>
struct TreeDP {
  int n, root;
  V<int> par;
  V<S> low, high;
  F f;
  G g;
  TreeDP(V<V<int>> t, V<S> prim, F f, G g, int r, S e)
    : n(t.size()), root(r), par(n, -1), low(prim), high(prim), f(move(f)), g(move(g))
  {
    V<int> bfs(n, r);
    int p = 1;
    for(int v : bfs) for(int w : t[v]){
      ranges::rotate(t[w], ranges::find(t[w], v) + 1);
      t[w].pop_back();
      par[bfs[p++] = w] = v;
    }
    REP(i, n - 1){
      int v = bfs[n - 1 - i], w = par[v];
      low[w] = f(g(low[v], v, w), low[w]);
    }
    for(int v : bfs){
      S s = prim[v];
      for(int w : t[v]){
        high[w] = s;
        s = f(s, g(low[w], w, v));
      }
      ranges::reverse(t[v]);
      s = v == r ? e : g(high[v], par[v], v);
      for(int w : t[v]){
        high[w] = f(s, high[w]);
        s = f(g(low[w], w, v), s);
      }
    }
  }
  S get(int v){
    if(v == root) return low[v];
    return f(low[v], g(high[v], par[v], v));
  }
};