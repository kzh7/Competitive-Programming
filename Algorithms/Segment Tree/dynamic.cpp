/*
  * Description
    * update on position, sum on range
    * dynamic segment tree 
*/

#include <bits/stdc++.h>

using namespace std;

const int N = (int)1e5 + 7;
const int INF = (int)1e9 + 7;
const int LOG = log2(INF) + 2;

int sz = 1;
int t[N * LOG], ls[N * LOG], rs[N * LOG];

void upd(int p, int x, int v = 1, int tl = 0, int tr = INF) {
  if (tl == tr) {
    t[v] += x;
    return;
  }
  int tm = tl + tr >> 1;
  if (p <= tm) {
    if (!ls[v]) ls[v] = ++sz;
    upd(p, x, ls[v], tl, tm);
  }
  else {
    if (!rs[v]) rs[v] = ++sz;
    upd(p, x, rs[v], tm + 1, tr);
  }
  t[v] = t[ls[v]] + t[rs[v]];
}
int get(int l, int r, int v = 1, int tl = 0, int tr = INF) {
  if (l <= tl && tr <= r) return t[v];
  if (tl > r || tr < l || !v) return 0;
  int tm = tl + tr >> 1; 
  return get(l, r, ls[v], tl, tm) + get(l, r, rs[v], tm + 1, tr);
}

int main() {
  upd(5, 2);
  upd(1e9, -3);
  cout << get(0, INF);
  return 0;
}
