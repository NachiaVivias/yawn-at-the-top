/*
LP
max cx
s.t. Ax <= b, x >= 0
time complexity: exponential. fast $O(HW^2)$ in experiment. dependent on
the modeling.
*/
template<class T>
struct LPsolver{
    const T eps = 1e-7;
    int type;
    T cx;
    V<T> sol; //W
    // 0: found solution, 1: infeasible, 2: unbounded
    LPsolver(VV<T> A, V<T> b, V<T> c){
        int H = A.size(), W = A[0].size();
        assert((int)b.size() == H);
        assert((int)c.size() == W);
        Left.resize(H);
        Down.resize(W);
        sol.resize(W);
        cx = 0;
        auto pivot = [&](int x, int y) {
            swap(Left[x], Down[y]);
            T k = A[x][y];
            A[x][y] = 1;
            vector<int> nz;
            REP(i,W){
                A[x][i] /= k;
                if (!eq(A[x][i], 0)) nz.push_back(i);
            }
            b[x] /= k;
            REP(i,H){
                if (i == x || eq(A[i][y], 0)) continue;
                k = A[i][y];
                A[i][y] = 0;
                b[i] -= k * b[x];
                for (int j : nz) A[i][j] -= k * A[x][j];
            }
            if (eq(c[y], 0)) return;
            k = c[y];
            c[y] = 0;
            cx += k * b[x];
            for (int i : nz) c[i] -= k * A[x][i];
        };
        REP(i,W) Down[i] = i;
        REP(i,H) Left[i] = W + i;
        while (1) { // Eliminating negative b[i]
            int x = -1, y = -1;
            REP(i,H) if(ls(b[i], 0) && (x == -1 || b[i] < b[x])) x = i;
            if (x == -1) break;
            REP(i,W) if(ls(A[x][i], 0) && (y == -1 || A[x][i] < A[x][y])) y = i;
            if (y == -1){
                type = 1; //infeasible
                cx = -1e100;
                return;
            }
            pivot(x, y);
        }
        while (1) {
            int x = -1, y = -1;
            REP(i,W) if(ls(0, c[i]) && (y == -1 || c[i] > c[y])) y = i;
            if (y == -1) break;
            REP(i,H) if(ls(0, A[i][y]) && (x == -1 || b[i] / A[i][y] < b[x] / A[x][y])) x = i;
            if (x == -1){
                type = 2; //unbounded
                cx = 1e100;
                return;
            }
            pivot(x, y);
        }
        REP(i,H) if (Left[i] < W) sol[Left[i]] = b[i];
        type = 0;
    }
    V<int> Left,Down; //H,W
    bool eq(T a, T b) { return fabs(a - b) < eps; }
    bool ls(T a, T b) { return a < b && !eq(a, b); }
};