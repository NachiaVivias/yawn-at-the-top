#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/challenges/sources/ICPC/Regional/1377"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define REP(i,n) for(ll i=0; i<ll(n); i++)

#include "src/other/surreal.hpp"

map<string, Surreal> dpmem;
vector<string> game_move(string s){
  vector<string> ans;
  for(int i=0; i<int(s.size()); i++) if(s[i] == 'W'){
    ans.push_back(s.substr(0, i));
  }
  return ans;
}
string game_flip(string s){
  for(char& c : s) c = (c == 'B') ? 'W' : 'B';
  return s;
}
Surreal dp(string s){
  if(s.empty()) return 0;
  if(dpmem.count(s)) return dpmem[s];
  auto nx0 = game_move(s);
  auto nx1 = game_move(game_flip(s));
  Surreal f = -1000;
  for(auto x : nx0) f = max(f, dp(x));
  Surreal g = -1000;
  for(auto x : nx1) g = max(g, dp(x));
  return dpmem[s] = (f | -g);
}

void testcase(){
  int N; cin >> N;
  vector<string> S(N); for(auto& s : S) cin >> s;
  vector<Surreal> F0, F1;
  vector<long long> sz0, sz1;
  for(int i=0; i<N; i++){
    auto s = dp(S[i]);
    F0.push_back(s);
    sz0.push_back(S[i].size());
    swap(F0, F1);
    swap(sz0, sz1);
  }
  vector<pair<Surreal, long long>> buf;
  for(int i=0; i<(1<<F0.size()); i++){
    long long cnt = 0;
    Surreal s = 0;
    for(int j=0; j<int(F0.size()); j++) if(i&(1<<j)){ s = s + F0[j]; cnt += sz0[j]; }
    buf.push_back({ s, -cnt });
  }
  sort(buf.begin(), buf.end());
  long long ans = 0;
  for(int i=0; i<(1<<F1.size()); i++){
    long long cnt = 0;
    Surreal s = 0;
    for(int j=0; j<int(F1.size()); j++) if(i&(1<<j)){ s = s + F1[j]; cnt += sz1[j]; }
    auto it = lower_bound(buf.begin(), buf.end(), make_pair(-s, -(1ll<<60)));
    if(it == buf.end() || (it->first + s).p) continue;
    ans = max(ans, cnt - it->second);
  }

  cout << ans << "\n";
}

int main(){
  cin.tie(0)->sync_with_stdio(0);
  testcase();
  return 0;
}