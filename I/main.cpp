#include <algorithm>
#include <iostream>
#include <vector>
std::vector<std::pair<int, int>> v;

int main() {
  int n;
  std::cin >> n;
  if (n == 0) {
    return 0;
  }
  if (n == 1) {
    int x, y;
    std::cin >> x >> y;
    std::cout << std::min(x, y) << '\n';
    return 0;
  }
  if (n == 2) {
    int x, y, z, t;
    std::cin >> x >> y >> z >> t;
    int min_val = std::abs(x - z);
    min_val = std::min(min_val, std::abs(x - t));
    min_val = std::min(min_val, std::abs(y - z));
    min_val = std::min(min_val, std::abs(y - t));
    std::cout << min_val << '\n';
    return 0;
  }
  for (int i = 0; i < n; i++) {
    int x, y;
    std::cin >> x >> y;
    if (x > y)
      std::swap(x, y);
    v.push_back(std::make_pair(x, y));
  }
  std::sort(v.begin(), v.end());
  // std::cout << '\n';
  // for (const auto &p : v) {
  //   std::cout << p.first << ' ' << p.second << '\n';
  // }
  // std::cout << '\n';
  int result = 1000000000;
  int max_val = 0, min_val_second = result;
  for (int i = 0; i < n; i++) {
    min_val_second =
        std::min(min_val_second, i == 0 ? min_val_second : v[i - 1].second);
    max_val = std::max(max_val, i == 0 ? 0 : v[i - 1].second);
    max_val = std::max(max_val, v.back().first);
    int min_val = std::min(v[i].first, min_val_second);
    result = std::min(result, max_val - min_val);
    // std::cout << i << ' ' << min_val << ' ' << max_val << '\n';
  }
  std::cout << result << '\n';
  return 0;
}
