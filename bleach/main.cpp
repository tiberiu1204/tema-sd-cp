#include <fstream>
#include <iostream>
#include <set>

std::ifstream in("bleach.in");
std::ofstream out("bleach.out");

int main() {
  int n, k;
  in >> n >> k;
  std::multiset<int> heap;
  int min_put = 0;
  long long put = 0;
  for (int i = 0; i < n; i++) {
    int x;
    in >> x;
    heap.insert(x);
    if (i >= k) {
      int top = *heap.begin();
      heap.erase(heap.begin());
      if (put < top) {
        min_put += (top - put);
        put = 2LL * top;
      } else {
        put += top;
      }
      if (put >= 1000000000) {
        out << min_put << '\n';
        return 0;
      }
    }
  }
  while (!heap.empty()) {
    int top = *heap.begin();
    heap.erase(heap.begin());
    if (put < top) {
      min_put += (top - put);
      put = 2LL * top;
    } else {
      put += top;
    }
    if (put >= 1000000000) {
      out << min_put << '\n';
      return 0;
    }
  }
  out << min_put << '\n';
}
