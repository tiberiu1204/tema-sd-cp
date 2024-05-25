#include <fstream>
#include <iostream>

std::ifstream in("euclid.in");
std::ofstream out("euclid.out");

int rmq[9][9][401][401];
int log_table[401];
int t, m, n, h, w;

int gcd(int a, int b) {
  if (a % b == 0)
    return b;
  if (b % a == 0)
    return a;
  return gcd(a % b, b % a);
}

inline int gcd4(int a, int b, int c, int d) {
  return gcd(gcd(a, b), gcd(c, d));
}

void calc_rmq() {
  for (int lg = 0; 1 << (lg + 1) <= n; lg++) {
    for (int i = 1; i <= m; i++) {
      for (int j = 1; j <= n - (1 << (lg + 1)) + 1; j++) {
        rmq[0][lg + 1][i][j] =
            gcd(rmq[0][lg][i][j], rmq[0][lg][i][j + (1 << lg)]);
      }
    }
  }
  for (int lg1 = 0; (1 << (lg1 + 1)) <= m; lg1++) {
    for (int lg2 = 0; (1 << lg2) <= n; lg2++) {
      for (int i = 1; i <= m - (1 << (lg1 + 1)) + 1; i++) {
        for (int j = 1; j <= n - (1 << lg2) + 1; j++) {
          rmq[lg1 + 1][lg2][i][j] =
              gcd(rmq[lg1][lg2][i][j], rmq[lg1][lg2][i + (1 << lg1)][j]);
        }
      }
    }
  }
}

inline int get_area_gcd(int i, int j) {
  int lg1 = log_table[h], lg2 = log_table[w];
  return gcd4(rmq[lg1][lg2][i][j], rmq[lg1][lg2][i][j + w - (1 << lg2)],
              rmq[lg1][lg2][i + h - (1 << lg1)][j],
              rmq[lg1][lg2][i + h - (1 << lg1)][j + w - (1 << lg2)]);
}

void solve(int test) {
  int max_gcd = 1;
  for (int i = 1; i <= m - h + 1; i++) {
    for (int j = 1; j <= n - w + 1; j++) {
      max_gcd = std::max(max_gcd, get_area_gcd(i, j));
    }
  }
  out << "Case #" << test << ": " << max_gcd << '\n';
}

int main() {
  for (int i = 2; i <= 400; i++) {
    log_table[i] = log_table[i / 2] + 1;
  }
  in >> t;
  for (int test = 1; test <= t; test++) {
    in >> m >> n >> h >> w;
    for (int i = 1; i <= m; i++) {
      for (int j = 1; j <= n; j++) {
        in >> rmq[0][0][i][j];
      }
    }
    calc_rmq();
    solve(test);
  }
}
