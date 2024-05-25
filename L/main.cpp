#include <cmath>
#include <iostream>
const constexpr int MOD = 1000000007;
int v[100000];
int rmq[18][100000];
long long optipow(int exp) {
  long long base = 2, remainder = 1;
  while (exp > 0) {
    if (exp % 2 == 0) {
      base *= base;
      base %= MOD;
      exp /= 2;
    } else {
      remainder *= base;
      remainder %= MOD;
      exp--;
    }
  }
  return remainder;
}
int main() {
  int n;
  std::cin >> n;
  for (int i = 0; i < n; i++) {
    std::cin >> v[i];
    rmq[0][i] = v[i];
  }
  for (int i = 1; (1 << i) <= n; i++) {
    for (int j = 0; j < n - (1 << i) + 1; j++) {
      rmq[i][j] = std::max(rmq[i - 1][j], rmq[i - 1][j + (1 << (i - 1))]);
    }
  }
  int m;
  std::cin >> m;
  for (int i = 0; i < m; i++) {
    int st, dr;
    std::cin >> st >> dr;
    int lg = std::log2(dr - st + 1);
    // std::cout << std::max(rmq[lg][st - 1], rmq[lg][dr - (1 << lg)]) << ' '
    //  << rmq[lg][st - 1] << ' ' << rmq[lg][dr - (1 << lg)] << '\n';
    std::cout << (optipow(dr - st) *
                  std::max(rmq[lg][st - 1], rmq[lg][dr - (1 << lg)])) %
                     MOD
              << '\n';
  }
}
