template<class S, class F, S e(), F id()>
struct LCNode {
    LCNode *c[2] = {0,0}, *p = 0;
    S a, sum, sum_r = e();
    F lz = id(), lz_r = id();
    ll rev = 0;
    void do_rev(){ rev ^= 1, swap(c[0], c[1]); }
    void apply(ll f){
        lz += f;
        lz_r += f;
        a.apply(f);
        sum.apply(f);
        sum_r.apply(f);
    }
    void prop(){
        if(rev) REP(t,2) if(c[t]) c[t]->do_rev();
        rev = 0;
        if(lz) REP(t,2) if(c[t]) c[t]->apply(lz);
        lz = id();
    }
    void agg(){
        sum = a;
        sum += sum_r;
        if(c[0]) sum = op(c[0] ->sum, sum);
        if(c[1]) sum = op(sum, c[1]->sum);
    }
    ll way(){
        REP(t,2) if(p && p->c[t] == this) return t;
        return -1;
    }
    void rot(){
        auto w = p;
        ll x = 1 - way();
        if(w->way() != -1) w->p->c[w->way()] = this;
        p = w->p;
        w->c[!x] = c[x];
        if(c[x]) c[x]->p = w;
        c[x] = w;
        w->p = this;
        w->agg(), agg();
    }
    void propall(){
        if(way() >= 0) p->propall();
        prop();
    }
    void splay(){
        for(propall(); way() >= 0; rot())
            if(p->way() != -1)
                (way() == p->way() ? p : this)->rot();
    }
    // splay tree ここまで
    void splice(LCNode* t){
        if (c[1]) sum_r += c[1]->sum, c[1]->apply(-lz_r);
        if (t) t->apply(lz_r), sum_r -= t->sum;
        c[1] = t, agg();
    }
    void expose(){
        for(auto t = this; t; t=t->p) t->splay();
        for(auto t=this; t->p; t=t->p) t->p->splice(t);
        splay(), splice(0);
    }
    void evert(){ expose(), do_rev(), prop(), agg(); }
    void link(LCNode* r){
        r->evert(), evert(), p=r;
        r->sum_r += sum, apply(-r->lz_r);
        r->agg();
    }
    void cut(){ expose(), c[0] = c[0]->p = 0, agg(); }
};
// using F = ll;
// struct S{
//     ll x;
//     void apply(F f){ x += f; }
//     S& operator+=(S r){ return *this; }  // rake
//     S& operator-=(S r){ return *this; }
// };
// S op(S l, S r){ return {min(l.x, r.x)}; }
// S e(){ return {INF}; }
// F operator-(F f);        // 逆作用