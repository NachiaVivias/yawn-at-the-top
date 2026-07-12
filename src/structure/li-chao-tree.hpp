template<class Func, class Eval>
struct LiChaoTreeFlexible{
    int n, N;
    vector<Func> A;
    vector<bool> vis;
    Eval ev;
    bool cmpat(Func fl, Func fr, int p){
        if(p >= n) p = n-1;
        return ev(fl, p) < ev(fr, p);
    }
    LiChaoTreeFlexible(int n, Func inf, Eval eval)
        : n(n)
        , N(bit_ceil(unsigned(n)))
        , A(N*2, inf)
        , vis(N*2, 0)
        , ev(move(eval))
    {}
    void addSegment(int l, int r, Func f){
        if(l >= r) return;
        auto dfs = [&](int i,Func f,int a,int b,auto& dfs) -> void {
            vis[i] = 1;
            if(i >= N * 2 || r <= a || b <= l) return;
            int m = (a+b)/2;
            if(!(l <= a && b <= r)){
                dfs(i*2,f,a,m,dfs);
                dfs(i*2+1,f,m,b,dfs);
                return;
            }
            if(cmpat(f, A[i], m)) swap(A[i],f);
            if(a + 1 == b) return;
            if (cmpat(f, A[i], a)) dfs(i * 2, f, a, m, dfs);
            if (cmpat(f, A[i], b - 1)) dfs(i * 2 + 1, f, m, b, dfs);
        };
        dfs(1,f,0,N,dfs);
    }
    void addLine(Func f){ addSegment(0,N,f); }
    Func minFunc(int p){
        int i = 1, l = 0, r = N;
        Func res = A[0];
        while(i < N * 2 && vis[i]){
            if(cmpat(A[i], res, p)) res = A[i];
            int m = (l+r)/2;
            i = i * 2 + (m <= p);
            (m <= p ? l : r) = m;
        }
        return res;
    }
};