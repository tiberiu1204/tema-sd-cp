#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

int v[250001][19];
std::unordered_map<int, int> map;

std::ifstream in("stramosi.in");
std::ofstream out("stramosi.out");

int main() {
  int n, m;
  in >> n >> m;
  for (int i = 1; i <= n; i++) {
    int stramos;
    in >> stramos;
    v[i][0] = stramos;
    for (int j = 1;; j++) {
      int first_jump = v[i][j - 1];
      if (first_jump == 0)
        break;
      int second_jump = v[first_jump][j - 1];
      if (second_jump == 0)
        break;
      v[i][j] = second_jump;
    }
  }
  for (int i = 0; i < m; i++) {
    int nod, nr_stramos;
    in >> nod >> nr_stramos;
    for (int k = 18; k >= 0; k--) {
      if (nr_stramos < (1 << k))
        continue;
      nod = v[nod][k];
      nr_stramos -= (1 << k);
      if (nod == 0 || nr_stramos == 0)
        break;
    }
    out << nod << '\n';
  }
}
