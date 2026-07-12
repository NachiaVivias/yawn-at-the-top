template <class T>
vector<int> cartesian_tree(const vector<T>& a) {
  int n = a.size(), t = 0;
  vector<int> pa(n, -1), st(n);
  REP(i, n){
    int pr = -1;
    while (t && a[i] < a[st[t - 1]]) pr = st[--t];
    if (pr != -1) pa[pr] = i;
    if (t) pa[i] = st[t - 1];
    st[t++] = i;
  }
  return pa;
}