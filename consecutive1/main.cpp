#include <cmath>
#include <iostream>

int rmq[19][100001];
int rMq[19][100001];
int d[100001];
int dp[100001];
int v[100001];

int main() {
  int n;
  std::cin >> n;
  for (int i = 1; i <= n; i++) {
    std::cin >> v[i];
    rmq[0][i] = v[i];
    rMq[0][i] = v[i];
  }
  for (int i = 1; (1 << i) <= n; i++) {
    for (int j = 1; j <= n - (1 << (i - 1)) + 1; j++) {
      rmq[i][j] = std::min(rmq[i - 1][j], rmq[i - 1][j + (1 << (i - 1))]);
      rMq[i][j] = std::max(rMq[i - 1][j], rMq[i - 1][j + (1 << (i - 1))]);
    }
  }
  int st = 1, dr = 1;
  while (dr <= n) {
    d[v[dr]]++;
    while (d[v[dr]] > 1) {
      dp[st] = dr - 1;
      d[v[st]]--;
      st++;
    }
    dr++;
  }
  while (st <= n) {
    dp[st] = dr - 1;
    st++;
  }
  int q;
  std::cin >> q;
  for (int i = 0; i < q; i++) {
    int x, y;
    std::cin >> x >> y;
    if (y > dp[x]) {
      std::cout << 0;
      continue;
    }
    int lg = std::log2(y - x + 1);
    int max_val = std::max(rMq[lg][x], rMq[lg][y - (1 << lg) + 1]);
    int min_val = std::min(rmq[lg][x], rmq[lg][y - (1 << lg) + 1]);
    std::cout << ((max_val - min_val) == (y - x));
  }
}
