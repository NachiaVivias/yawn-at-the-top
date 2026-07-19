#define PROBLEM "https://yukicoder.me/problems/no/2149"

/*

No.2149 Vanitas Vanitatum

フック長公式

*/



#define _GLIBCXX_DEBUG

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = 1ll << 60;
#define REP(i,n) for(ll i=0; i<ll(n); i++)
template <class T> using V = vector<T>;
template <class A, class B> void chmax(A& l, const B& r){ if(l < r) l = r; }
template <class A, class B> void chmin(A& l, const B& r){ if(r < l) l = r; }

#include "src/number-theory/modint.hpp"
using Mint = ModInt<998244353, 3>;
#include "src/other/hook_length_formula.hpp"

Mint hook(string s){
    vector<int> A;
    int a = 0;
    for(char c : s) if(c == '0') a++;
    for(char c : s){
        if(c == '0'){ a--; }
        if(c == '1'){ A.push_back(a); }
    }
    reverse(A.begin(), A.end());
    return Hook_Length_Formula(A);
}

int opcount(string s){
    int ans = 0;
    REP(i,s.size()) REP(j,i) if(s[i] == '0' && s[j] == '1') ans++;
    return ans;
}


void testcase(){
    int N; cin >> N;
    vector<int> A(N+1); REP(i,N) cin >> A[i+1];
    string S;
    REP(i,N){
        REP(j,A[i+1]-A[i]) S.push_back('1');
        S.push_back('0');
    }

    string S2[2];
    REP(i,S.size()) S2[i%2].push_back(S[i]);
    
    ll opc0 = opcount(S2[0]);
    ll opc1 = opcount(S2[1]);

    Mint ans = 1;
    for(ll i=1; i<=opc0; i++) ans *= i;
    ans = ans.inv();
    for(ll i=1; i<=opc0; i++) ans *= opc1 + i;
    ans *= hook(S2[0]) * hook(S2[1]);

    REP(t,2) sort(S2[t].begin(), S2[t].end());

    string S3;
    REP(i,S.size()) S3.push_back(S2[i%2][i/2]);

    if(S3.find("10") != string::npos) ans = 0;
    cout << ans.v << '\n';
}

int main(){
  cin.tie(0)->sync_with_stdio(0);
  testcase();
  return 0;
}
