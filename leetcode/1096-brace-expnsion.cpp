class Solution {
public:
  vector<string> braceExpansionII(string expression) {
    int L = 0;
    auto t = dfs(expression, L);
    return vector<string>(t.begin(), t.end());
  }
  set<string> append(set<string> S, char c) {
    set<string> T;
    for (auto s: S) {
      s.push_back(c);
      T.insert(s);
    }
    return T;
  }
  set<string> mul(set<string> A, set<string> B) {
    set<string> C;
    for (auto a: A) {
      for (auto b: B) C.insert(a + b);
    }
    return C;
  }
  set<string> add(set<string> A, set<string> B) {
    for (auto b: B) A.insert(b);
    return A;
  }
  set<string> dfs(string &e, int &L) {
    set<string> ans;
    set<string> cur = {""};
    while (L < e.size()) {
      if (e[L] == ' ' ) {
        L++;
        continue;
      }
      if (e[L] == '{') {
        L++;
        cur = mul(cur, dfs(e, L));
      } else if (e[L] == ',') {
        ans = add(ans, cur);
        cur = {""};
        L++;
      } else if (e[L] == '}') {
        ans = add(ans, cur);
        L++;
        return ans;
      } else {
        cur = append(cur, e[L]);
        L++;
      }
    }
    ans = add(ans, cur);
    return ans;
  }
  
};

