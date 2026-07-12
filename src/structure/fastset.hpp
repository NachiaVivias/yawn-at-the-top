/// Original : ICPC_notebook (https://github.com/tatyam-prime/ICPC_notebook/blob/main/src/data-structure/FastSet.hpp)
struct FS {
  using U = unsigned long long;
  const U B = 64;
  U n;
  V<V<U>> a;
  FS(U n) : n(n) {
    do a.emplace_back(n = (n + B - 1) / B);
    while(n > 1);
  }
  bool operator[](ll i) const { return a[0][i / B] >> (i % B) & 1; }
  void insert(ll i) {
    for(auto& v : a) {
      v[i / B] |= 1ULL << (i % B);
      i /= B;
    }
  }
  void erase(ll i) {
    for(auto& v : a) {
      v[i / B] &= ~(1ULL << (i % B));
      if(v[i / B]) break;
      i /= B;
    }
  }
  ll next(ll i) {  // no less than i
    REP(h, a.size()) {
      if(i / B >= a[h].size()) break;
      U d = a[h][i / B] >> (i % B);
      if(d) {
        i += countr_zero(d);
        while(h--) i = i * B + countr_zero(a[h][i]);
        return i;
      }
      i = i / B + 1;
    }
    return -1;
  }
  ll prev(ll i) { // no greater than i
    REP(h, a.size()) {
      if(i < 0) break;
      U d = a[h][i / B] << (~i % B);
      if(d) {
        i -= countl_zero(d);
        while(h--) i = i * B + __lg(a[h][i]);
        return i;
      }
      i = i / B - 1;
    }
    return -1;
  }
};