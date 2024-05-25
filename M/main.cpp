#include <cmath>
#include <iostream>
using namespace std;
int rmq[19][200000];
int v[200000];
inline int get_min_pos(int st, int dr) {
  int lg = log2(dr - st + 1);
  int left = v[rmq[lg][st]];
  int right = v[rmq[lg][dr - (1 << lg) + 1]];
  if (left < right)
    return rmq[lg][st];
  else if (left > right)
    return rmq[lg][dr - (1 << lg) + 1];
  else
    return max(rmq[lg][st], rmq[lg][dr - (1 << lg) + 1]);
}
inline long long calc_interesting(int st, int dr, int min_pos) {
  long long left = min_pos - st;
  long long right = dr - min_pos;
  if (left <= right)
    return left * (left + 1) / 2;
  else
    return (right + 1) * (left - right) + (right + 1) * right / 2;
}
long long solve(int st, int dr) {
  if (st >= dr)
    return 0;
  int min_pos = get_min_pos(st, dr);
  // cout << st << ' ' << dr << ' ' << min_pos << ' ' << ' '
  //   << calc_interesting(st, dr, min_pos) << '\n';
  return calc_interesting(st, dr, min_pos) + solve(st, min_pos - 1) +
         solve(min_pos + 1, dr);
}
int main() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> v[i];
    rmq[0][i] = i;
  }
  for (int i = 1; (1 << i) <= n; i++) {
    for (int j = 0; j < n - (1 << i) + 1; j++) {
      int left = v[rmq[i - 1][j]];
      int right = v[rmq[i - 1][j + (1 << (i - 1))]];
      if (left < right)
        rmq[i][j] = rmq[i - 1][j];
      else if (left > right)
        rmq[i][j] = rmq[i - 1][j + (1 << (i - 1))];
      else
        rmq[i][j] = max(rmq[i - 1][j], rmq[i - 1][j + (1 << (i - 1))]);
    }
  }
  cout << solve(0, n - 1) << '\n';
}
