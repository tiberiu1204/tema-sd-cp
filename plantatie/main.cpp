#include <cmath>
#include <fstream>
#include <iostream>

int rmq[10][501][501];

std::ifstream in("plantatie.in");
std::ofstream out("plantatie.out");

int query(int x, int y, int w) {
  int x1 = x + w - 1, y1 = y + w - 1;
  int lg = std::log2(w);
  int p = (1 << lg);
  int res = rmq[lg][x][y];
  res = std::max(res, rmq[lg][x1 - p + 1][y]);
  res = std::max(res, rmq[lg][x][y1 - p + 1]);
  res = std::max(res, rmq[lg][x1 - p + 1][y1 - p + 1]);
  return res;
}

int main() {
  int n, m;
  in >> n >> m;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      in >> rmq[0][i][j];
    }
  }
  for (int pow = 1; (1 << pow) <= n; pow++) {
    for (int i = 1; i <= n - (1 << pow) + 1; i++) {
      for (int j = 1; j <= n - (1 << pow) + 1; j++) {
        rmq[pow][i][j] =
            std::max(rmq[pow - 1][i][j], rmq[pow - 1][i + (1 << (pow - 1))][j]);
        rmq[pow][i][j] =
            std::max(rmq[pow][i][j], rmq[pow - 1][i][j + (1 << (pow - 1))]);
        rmq[pow][i][j] =
            std::max(rmq[pow][i][j],
                     rmq[pow - 1][i + (1 << (pow - 1))][j + (1 << (pow - 1))]);
      }
    }
  }
  for (int i = 0; i < m; i++) {
    int x, y, w;
    in >> x >> y >> w;
    out << query(x, y, w) << '\n';
  }
}
