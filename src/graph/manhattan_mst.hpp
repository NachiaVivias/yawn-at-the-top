/// Original: ei1333 https://ei1333.github.io/library/graph/mst/manhattan-mst.hpp
// 候補の辺を O(N) 本に減らす。MST時は追加でsort, UF等の必要あり。
template<typename T> V<tuple<T, int, int>>
manhattan_mst(V<T> xs, V<T> ys) {
    assert(xs.size() == ys.size());
    V<tuple<T, int, int>> ret;
    int n = (int)xs.size();
    V<int> ord(n);
    REP(i,n) ord[i] = i;
    auto cmp = [&](int i, int j) { return xs[i] + ys[i] < xs[j] + ys[j]; };
    REP(s,4){
        sort(ord.begin(), ord.end(), cmp);
        map<T, int> idx;
        for(int i : ord) {
            for(auto it = idx.lower_bound(-ys[i]); it != idx.end(); it = idx.erase(it)) {
                int j = it->second;
                if(xs[i] - xs[j] < ys[i] - ys[j]) break;
                ret.emplace_back(abs(xs[i] - xs[j]) + abs(ys[i] - ys[j]), i, j);
            }
            idx[-ys[i]] = i;
        }
        swap(xs, ys);
        if(s%2) REP(i,n) xs[i] *= -1;
    }
    return ret;
}