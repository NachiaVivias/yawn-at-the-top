// x = lx + p * i ( 0 <= i < len ) なる点において
// x = argmin_t [0<=t<=x] : (a * t + b) % m
struct MinModResult {
    ll lx, rx, p, len;
};
V<MinModResult> MinModLinear(ll m, ll a, ll b){
  V<MinModResult> res;
  res.push_back({0,0,1,1});
  if(!b || !a) return res;
  a = m - a;
  ll d = b, x = 0, r = 0, aa = a, mm = m;
  auto addRes = [&](ll dx, ll dy) -> void {
    r = d / dy, d %= dy;
    res.push_back({ x + dx, x + dx * r, dx, r });
    x += dx * r;
  };
  if(a <= d) addRes(1, a);
  ll f[3] = {0,1}, g[3] = {1,0}, e[3], t0, t1;
  while(mm){
    t0 = aa / mm, aa %= mm;
    f[2] = f[0] + f[1] * t0, g[2] = g[0] + g[1] * t0;
    if(t0 != 0){
      REP(i,3) e[i] = a * g[i] - m * f[i];
      while(e[2] <= d){
        ll t = max((e[0] - d - e[1] - 1) / -e[1], 0ll);
        if(e[0] + e[1] * t == 0) break;
        addRes(g[0] + g[1] * t, e[0] + e[1] * t);
      }
      f[0] = f[2], g[0] = g[2];
      if(!e[2]) break;
    }
    if(!aa) break;
    t1 = mm / aa, mm %= aa;
    f[1] += f[0] * t1, g[1] += g[0] * t1;
  }
  return res;
}