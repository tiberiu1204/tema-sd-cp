#include <cmath>
#include <iostream>

int rmq[32][200000];
int v[200000];

struct Node {
  Node *left;
  Node *right;
} *trie;

void insert(int val) {
  Node *it = trie;
  for (int i = 31; i >= 0; i--) {
    int bit = (val >> i) & 1;
    if (bit == 0) {
      if (!it->left)
        it->left = new Node();
      it = it->left;
    } else {
      if (!it->right)
        it->right = new Node();
      it = it->right;
    }
  }
}

int query(int right) {
  int val = v[right];
  int max_xor = 0;
  Node *it = trie;
  for (int i = 31; i >= 0; i--) {
    int bit = (val >> i) & 1;
    if (bit == 0 && it->right) {
      it = it->right;
      max_xor += (1 << i);
    } else if (bit == 1 && it->left) {
      it = it->left;
      max_xor += (1 << i);
    } else {
      it = it->left ? it->left : it->right;
    }
  }
  return max_xor;
}

int query_rmq(int left, int right) {
  int lg = std::log2(right - left);
  int st = rmq[lg][left];
  int dr = rmq[lg][right - (1 << lg)];
  if (v[st] > v[dr])
    return st;
  else
    return dr;
}

int main() {
  int n;
  std::cin >> n;
  trie = new Node();
  for (int i = 0; i < n; i++) {
    std::cin >> v[i];
    rmq[0][i] = i;
  }
  for (int i = 1; (1 << i) <= n; i++) {
    for (int j = 0; j < n - (1 << (i - 1)); j++) {
      int left = rmq[i - 1][j];
      int right = rmq[i - 1][j + (1 << (i - 1))];
      if (v[left] > v[right])
        rmq[i][j] = left;
      else
        rmq[i][j] = right;
    }
  }
  insert(v[0]);
  insert(v[1]);
  long long result = 0;
  int max_xor = 0;
  for (int i = 2; i < n - 1; i++) {
    max_xor = std::max(query(i - 1), max_xor);
    int max_pos = query_rmq(i, n);
    int t1 = v[max_pos];
    int t2;
    if (max_pos == i) {
      t2 = v[query_rmq(i + 1, n)];
    } else if (max_pos == n - 1) {
      t2 = v[query_rmq(i, n - 1)];
    } else {
      t2 = std::max(v[query_rmq(i, max_pos)], v[query_rmq(max_pos + 1, n)]);
    }
    result = std::max(result, 1LL * (t1 + t2) * max_xor);
    insert(v[i]);
  }
  std::cout << result << '\n';
}
