/// BEGIN https://github.com/NachiaVivias/yawn-at-the-top/blob/main/src/tree/link_cut_tree_subtree.hpp
template<class S, class F, S e(), F id()>
struct LCNode {
    LCNode *c[2] = {0, 0}, *p = 0;
    S a, path, rake = e();
    F lz = id(), lzr = id();
    ll rev = 0;
    void do_rev(){
      rev ^= 1, swap(c[0], c[1]);
      a.rev(), path.rev();
    }
    void apply(F f){
        lz.apply(f);
        lzr.apply(f); // 最悪ここだけ消せばパス作用になる
        a.apply(f);
        path.apply(f);
        rake.apply(f);
    }
    void prop(){
        if(rev) REP(t, 2) if(c[t]) c[t]->do_rev();
        rev = 0;
        REP(t, 2) if(c[t]) c[t]->apply(lz);
        lz = id();
    }
    void agg(){
        path = a;
        path += rake;
        if (c[0]) path = op(c[0]->path, path);
        if (c[1]) path = op(path, c[1]->path);
    }
    ll way(){
        REP(t, 2) if(p && p->c[t] == this) return t;
        return -1;
    }
    void rot(){
        auto w = p;
        ll x = !way();
        if (w->way() != -1) w->p->c[w->way()] = this;
        p = w->p;
        w->c[!x] = c[x];
        if (c[x]) c[x]->p = w;
        c[x] = w;
        w->p = this;
        w->agg(), agg();
    }
    void propall(){
        if (way() != -1) p->propall();
        prop();
    }
    void splay(){
        for (propall(); way() != -1; rot())
            if (p->way() != -1)
                (way() == p->way() ? p : this)->rot();
    }
    // splay tree ここまで
    void splice(LCNode* t){
        if (c[1]) rake += c[1]->path, c[1]->apply(-lzr);
        if (t) t->apply(lzr), rake -= t->path;
        c[1] = t, agg();
    }
    void expose(){
        for(auto t = this; t; t = t->p) t->splay();
        for(auto t = this; t->p; t = t->p) t->p->splice(t);
        splay(), splice(0);
    }
    void evert(){ expose(), do_rev(), prop(), agg(); }
    void link(LCNode* r){
        r->evert(), evert(), p = r;
        r->rake += path, apply(-r->lzr);
        r->agg();
    }
    void cut(){ expose(), c[0] = c[0]->p = 0, agg(); }
};

struct F {
  void apply(F f){}
  F operator-() const { return {}; }
};
F id(){ return {}; }
struct S{
  void apply(F f){}
  S& operator+=(S r){ return *this; }  // rake
  S& operator-=(S r){ return *this; }
  void rev(){}
};
S op(S l, S r){ return {}; }
S e(){ return {}; }
/// END https://github.com/NachiaVivias/yawn-at-the-top/blob/main/src/tree/link_cut_tree_subtree.hpp
