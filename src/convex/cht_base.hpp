/// Original : Nachia
// a / b
// only max query supported
struct Frac {
  using Z = ll;
  Z a, b;
  Frac(Z x = 0, Z y = 1) : a(x), b(y) {
    if(b<0) a = -a, b = -b;
  }
  Z z() const { return a / b - ((a ^ b) < 0 && a % b); }
  friend auto operator<=>(Frac l, Frac r){
    Z lz = l.z(), rz = r.z();
    if(lz != rz) return lz <=> rz;
    return (l.a - lz * l.b) * r.b <=> (r.a - rz * r.b) * l.b;
  }
  Frac operator-() const { return {-a, b}; }
};
const Frac InfFrac = { 1ll << 61, 1 };
struct Line {
  ll a, b;
  Frac crossX(Line r) const {
    if(a == r.a) return b < r.b ? -InfFrac : InfFrac;
    return Frac(r.b - b, a - r.a);
  }
  friend auto operator<=>(Line l, Line r){
    return l.a != r.a ? l.a <=> r.a : l.b <=> r.b;
  }
};