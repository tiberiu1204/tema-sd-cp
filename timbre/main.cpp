#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
std::ifstream in("timbre.in");
std::ofstream out("timbre.out");
int main() {
  int n, m, k;
  in >> n >> m >> k;
  std::multiset<std::pair<int, int>, std::greater<std::pair<int, int>>> heap;
  for (int i = 0; i < m; i++) {
    int x, y;
    in >> x >> y;
    heap.insert({x, y});
  }
  int sum = 0;
  std::multiset<int> costuri;
  while (n > 0) {
    while (!heap.empty() && heap.begin()->first >= n) {
      costuri.insert(heap.begin()->second);
      heap.erase(heap.begin());
    }
    sum += *costuri.begin();
    costuri.erase(costuri.begin());
    n -= k;
  }
  out << sum << '\n';
}
