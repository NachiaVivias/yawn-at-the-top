struct S{ ll x; };
static S op(S l, S r){ return { l.x + r.x }; }
struct LCNode {
    LCNode* c[2] = {0,0}, * p = 0;
    S a, sum;
    int rev = 0;
    void do_rev(){ rev ^= 1, swap(c[0], c[1]), agg(); }
    void prop(){
        if(rev) REP(t, 2) if(c[t]) c[t]->do_rev();
        rev = 0;
    }
    void agg(){
        sum = a;
        if(c[0]) sum = op(c[0]->sum, sum);
        if(c[1]) sum = op(sum, c[1]->sum);
    }
    int way(){
        REP(t, 2) if(p && p->c[t] == this) return t;
        return -1;
    }
    void rot(){
        auto w = p;
        int x = way();
        if(w->way() != -1) w->p->c[w->way()] = this;
        p = w->p;
        w->c[x] = c[!x];
        if(c[x^1]) c[!x]->p = w;
        c[!x] = w;
        w->p = this;
        w->agg(), agg();
    }
    void propall(){
        if(way() >= 0) p->propall();
        prop();
    }
    void splay(){
        for(propall(); way() >= 0; rot()) if(p->way() != -1)
            (way() == p->way() ? p : this)->rot();
    }
    void expose(){
        for(auto t=this; t; t = t->p) t->splay();
        for(auto t=this; t->p; t=t->p){
            t->p->c[1] = t;
            t->p->agg();
        }
        splay(), c[1] = 0, agg();
    }
    void evert(){ expose(), do_rev(); }
    void link(LCNode* r){ r->evert(), evert(), p = r; }
    void cut(){ expose(), c[0] = c[0]->p = 0; }
};