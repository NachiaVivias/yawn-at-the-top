struct NimberManager{
  using ull = unsigned long long;
  ull h[256][256] = {}, g[256];
  NimberManager(){
    h[1][1] = 1;
    for(int d : {2,4,16}){
      REP(w, d) REP(x, d) REP(y, d) REP(z, d){
        if(x || z) {
          ull buf = (h[x][z] ^ h[x][y] ^ h[w][z]) * d;
          buf ^= h[d / 2][h[x][z]] ^ h[w][y];
          h[x * d + w][z * d + y] = buf;
        }
      }
    }
    REP(x, 256) REP(y, 256) if(h[x][y] == 1) g[x] = y;
  }
  ull mul(ull a, ull b, int d = 64){
      if(!(a && b)) return 0;
      if(d <= 8) return h[a][b];
      d /= 2;
      ull lm = (1ull << d) - 1;
      ull x = mul(a >> d, b >> d, d);
      ull y = mul(a & lm, b & lm, d);
      ull z = mul(a >> d ^ a & lm, b >> d ^ b & lm, d);
      ull buf = ((z ^ y) << d) ^ y;
      return buf ^ mul((ull)1 << (d - 1), x, d);
  }
  ull inv(ull a, int d = 64) {
    if (a < 256) return g[a];
    d /= 2;
    ull x = a >> d, y = a - (x << d);
    ull z = mul(mul(x, x, d), 1ULL << (d - 1));
    ull s = inv(mul(x ^ y, y, d) ^ z, d);
    return mul(s, x, d) << d ^ mul(s, x ^ y, d);
  }
};