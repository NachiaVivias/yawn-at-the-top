// 点群 (x,(A*x+B)%M) (x=0,1...N-1) を
// (start_x + dx*i, start_y + dy*i) (i=0,1...len-1) に分解
// lines.size() ~ O(sqrt(N))
template<class Int>
auto sqrt_lines(Int N, Int M, Int A, Int B) {
    struct SqrtLinesResult{
        struct Lines {
            Int start_x, start_y, len;
        };
        V<Lines> lines;
        Int dx, dy;
    };

    A = (A % M + M) % M;
    B = (B % M + M) % M;
    Int n = 1;
    while((n + 1) * (n + 1) <= N) n++;
    Int wid = min(A, M - A), dx = 1, h = 0;
    REP(x, n){
        if((h += A) >= M) h -= M;
        Int d = min(h, M - h);
        if(d < wid) wid = d, dx = x + 1;
    }
    Int dy = dx * A % M;
    if(M - dy < dy) dy -= M;
    SqrtLinesResult res;
    res.dx = dx, res.dy = dy;
    for(Int sx=0; sx<dx && sx<N; sx++){
        Int pt = sx - dx;
        while(pt + dx < N){
            pt += dx;
            Int t = (N - 1 - pt) / dx;
            Int fpt = (A * pt + B) % M;
            if(dy > 0) t = min(t, (M - 1 - fpt) / dy);
            if(dy < 0) t = min(t, fpt / -dy);
            res.lines.push_back({ pt, fpt, t + 1 });
            pt += t * dx;
        }
    }
    return res;
};