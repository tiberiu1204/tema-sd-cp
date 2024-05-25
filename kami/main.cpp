#include <fstream>
#include <iostream>

std::ifstream in("kami.in");
std::ofstream out("kami.out");

int n, m, v[100000];

int main() {
  in >> n;
  for (int i = 0; i < n; i++) {
    in >> v[i];
  }
  in >> m;
  for (int i = 0; i < m; i++) {
    int type, val;
    in >> type;
    if (type == 0) {
      int pos;
      in >> pos;
      pos--;
      in >> v[pos];
    } else {
      int b;
      in >> b;
      b--;
      int h = v[b];
      if (b == 0)
        out << 0 << '\n';
      for (int j = b - 1; j >= 0; j--) {
        if (h >= 1000000000) {
          out << 0 << '\n';
          break;
        } else if (v[j] >= h) {
          out << j + 1 << '\n';
          break;
        } else {
          h += v[j];
          if (j == 0) {
            out << 0 << '\n';
          }
        }
      }
    }
  }
}
