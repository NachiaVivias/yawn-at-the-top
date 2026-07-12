// x^2=N(mod p : prime) となるxを返す(存在しないなら-1)
// pow_mod(a,b,p)はa^b(mod p)
ll Tonelli_Shanks(ll N, ll p) {
  N %= p;
  if (p == 2) return N;
  if (pow_mod(N, p / 2, p) == p - 1) return -1;
  if (p % 4 == 3) return pow_mod(N, (p + 1) / 4, p);
  ll n = 1, pp = p - 1, c = 0;
  while (pow_mod(n, p / 2, p) != p - 1) n++;
  while (pp % 2 == 0) pp /= 2, c++;
  ll s = pow_mod(N, pp, p);
  ll r = pow_mod(N, (pp + 1) / 2, p);
  for (int i = c - 2; i >= 0; --i) {
    if (pow_mod(s, 1LL << i, p) == p - 1) {
      s = s * pow_mod(n, p >> (1 + i), p) % p;
      r = r * pow_mod(n, p >> (2 + i), p) % p;
    }
  }
  return r;
}