#include <fstream>
#include <iostream>

std::ifstream in("pikachu.in");
std::ofstream out("pikachu.out");

int n, k, v[100000];

long long check(int h) {
  long long res = 0;
  long long sum = 0;
  for (int i = 0; i < k; i++) {
    sum += std::abs(h - v[i]);
  }
  res = sum;
  for (int i = k; i < n; i++) {
    sum -= std::abs(h - v[i - k]);
    sum += std::abs(h - v[i]);
    res = std::min(res, sum);
  }
  return res;
}

int main() {
  in >> n >> k;
  int maxh = 0;
  long long res = 0;
  for (int i = 0; i < n; i++) {
    in >> v[i];
    maxh = std::max(maxh, v[i]);
    res += v[i];
  }
  int st = 0, dr = maxh;
  while (st <= dr) {
    int mij = (st + dr) / 2;
    long long c1 = check(mij), c2 = check(mij + 1);
    if (c1 < c2) {
      dr = mij - 1;
      res = std::min(res, c1);
    } else {
      st = mij + 1;
      res = std::min(res, c2);
    }
  }
  out << res << '\n';
}
