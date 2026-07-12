/// Original: Gifted Infants(SuffixAutomaton) https://yosupo.hatenablog.com/entry/2019/07/02/122433
struct SuffixAutomaton{
  using Char = char;
  using Str = string;

  /*
    Node information

    構築時に作る情報を増やしたいなら、
      - Node の定義
      - MakeNode() での初期化
      - clone のときの deep copy
    を変更する
    
    len :
      マッチするsubstrのうちlongest (4)
  */
  struct Node{
    using NP = Node*;
    int id;
    int len;
    NP link;
    map<Char,NP> next;

    Node(){}
    int getLongest(){ return len; }
    int getShortest(){ return link ? link->len+1 : 0; }
    void putNext(Char c, NP to){ next[c] = to; }
    bool hasNext(Char c){ return next.count(c); }
    NP getNext(Char c){ return hasNext(c) ? next[c] : 0; }
  };
  using NP = Node*;
  NP last;
  int sz; // the number of nodes
  V<NP> nodes;
  SuffixAutomaton(int N) : sz(0), nodes(2 * N, 0) {
    last = nodes[0] = MakeNode(0);
  }

  NP MakeNode(int len){
    NP v = nodes[sz] = new Node();
    v->id = sz++;
    v->len = len;
    v->link = 0;
    return v;
  }
  /*
    Add c to nodes[last]
    return the new node id
  */
  void add_char(Char c){
    NP p = last;
    last = MakeNode(last->len + 1);
    for(; p && !p->hasNext(c); p = p->link) p->next[c] = last;
    if(!p){
      last->link = nodes[0];
    }else{
      NP q = p->getNext(c);
      if(p->len+1 == q->len){
        last->link = q;
        return;
      }
      //clone!
      NP w = MakeNode(p->len + 1);
      /*
        deep copy !
      */
      w->next = q->next;
      w->link = q->link;
      for(; p && p->getNext(c) == q; p = p->link) p->next[c] = w;
      q->link = last->link = w;
    }
  }
  void TopologicalSort(){
    V<int> deg(sz);
    V<NP> ord(sz);
    REP(v,sz) for(auto it: nodes[v]->next) deg[it.second->id]++;
    ord[0] = nodes[0];
    int idx = 1;
    for(NP n : ord) for(auto it: nodes[n->id]->next) if(!--deg[it.second->id]) ord[idx++] = it.second;
    swap(nodes, ord);
    REP(i,sz) nodes[i]->id = i;
  }
};