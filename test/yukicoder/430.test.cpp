#define PROBLEM "https://yukicoder.me/problems/no/430"

#define _GLIBCXX_DEBUG

#include <bits/stdc++.h>
using namespace std;
template <class T>
using V = vector<T>;

#include "src/string/aho-corasick.hpp"

int main() {
    string s; cin >> s;
    int m; cin >> m;
    vector<string> c(m);
    for(auto& cc : c) cin >> cc;
    auto aho = ACTrie::make(c);
    int ans = 0;
    auto op = [&](int , int) { ans++; };
    aho->match(s, op);
    cout << ans << '\n';
}

