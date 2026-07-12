/// Original: Gifted Infants(Dominator Tree) https://yosupo.hatenablog.com/entry/2019/07/02/122433
struct DominatorTree{
    int n;
    V<V<int>> g,rG,bct;
    V<int> idom,semi,us,id,rId,par,mn,anc;
    DominatorTree(int nn):
        n(nn),
        g(n), rG(n), bct(n),
        idom(n,-1), semi(n), us(n), id(n,-1), rId(n), par(n,-1), mn(n), anc(n,-1)
    {
        REP(i,n) semi[i]=mn[i]=i;
    }
    void AddEdge(int a,int b){
        g[a].push_back(b);
        rG[b].push_back(a);
    }
    int Find(int v){
        if(anc[v]==-1) return v;
        int w = anc[v], a = Find(w);
        if(id[semi[mn[w]]]<id[semi[mn[v]]]) mn[v]=mn[w];
        return anc[v]=a;
    }
    void dfs(int v,int p,int& i){
        if(id[v]!=-1) return;
        id[v]=i;
        rId[i++]=v;
        par[v]=p;
        for(int c:g[v]) dfs(c,v,i);
    }
    V<int> Calc(int root){
        int sz=0;
        dfs(root,-1,sz);
        for(int i=sz-1;i>0;i--){
            int w=rId[i], &x = semi[w];
            for(int v:rG[w])if(id[v]!=-1){
                Find(v);
                if(id[semi[mn[v]]]<id[x]) x=semi[mn[v]];
            }
            bct[x].push_back(w);
            for(int v : bct[par[w]]) Find(v), us[v]=mn[v];
            bct[par[w]] = {};
            anc[w] = par[w];
        }
        for(int i=1; i<sz; i++){
            int w = rId[i], x = semi[w];
            idom[w] = x == semi[us[w]] ? x : idom[us[w]];
        }
        return idom;
    }
};