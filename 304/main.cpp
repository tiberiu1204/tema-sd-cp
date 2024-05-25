#include <iostream>
long long v[100000];
int n, q;

struct Node {
  long long total_sum;
  long long max_prefix;
  long long max_sufix;
  long long max_sum;
  Node() {}
  Node(long long total_sum, long long max_prefix, long long max_sufix,
       long long max_sum)
      : total_sum(total_sum), max_prefix(max_prefix), max_sufix(max_sufix),
        max_sum(max_sum) {}
} aint1[200000], aint2[200000];

void update(int st, int dr, long long val, int pos, int index, Node *aint) {
  if (st == dr) {
    aint[index] = Node(val, val, val, val);
    return;
  }
  int mid = (st + dr) / 2;
  if (pos <= mid) {
    update(st, mid, val, pos, 2 * index + 1, aint);
  } else {
    update(mid + 1, dr, val, pos, 2 * index + 2, aint);
  }
  Node *left = aint + 2 * index + 1;
  Node *right = aint + 2 * index + 2;
  Node *node = aint + index;
  node->total_sum = left->total_sum + right->total_sum;
  node->max_prefix =
      std::max(left->max_prefix, left->total_sum + right->max_prefix);
  node->max_sufix =
      std::max(right->max_sufix, left->max_sufix + right->total_sum);
  node->max_sum = std::max(left->max_sum, right->max_sum);
  node->max_sum = std::max(node->max_sum, left->max_sufix + right->max_prefix);
}

void build(Node *aint) {
  for (int i = 0; i < n; i++) {
    update(0, n - 1, v[i], i, 0, aint);
  }
}

Node query(int st, int dr, int l, int r, int index, Node *aint) {
  if (st >= l && dr <= r)
    return aint[index];
  if (dr < l || st > r || st > dr)
    return Node(0, 0, 0, 0);
  int mid = (st + dr) / 2;
  Node left = query(st, mid, l, r, 2 * index + 1, aint);
  Node right = query(mid + 1, dr, l, r, 2 * index + 2, aint);
  Node node;
  node.total_sum = left.total_sum + right.total_sum;
  node.max_prefix =
      std::max(left.max_prefix, left.total_sum + right.max_prefix);
  node.max_sufix = std::max(right.max_sufix, left.max_sufix + right.total_sum);
  node.max_sum = std::max(left.max_sum, right.max_sum);
  node.max_sum = std::max(node.max_sum, left.max_sufix + right.max_prefix);
  return node;
}

int main() {
  std::cin >> n >> q;
  for (int i = 0; i < n; i++) {
    std::cin >> v[i];
    if (i % 2 == 1) {
      v[i] = -v[i];
    }
  }
  build(aint1);
  for (int i = 0; i < n; i++) {
    v[i] = -v[i];
  }
  build(aint2);
  for (int i = 0; i < q; i++) {
    int t, x, y;
    std::cin >> t >> x >> y;
    x--;
    if (t == 1) {
      if (x % 2 == 1)
        y = -y;
      update(0, n - 1, y, x, 0, aint1);
      update(0, n - 1, -y, x, 0, aint2);
    } else {
      y--;
      std::cout << std::max(query(0, n - 1, x, y, 0, aint1).max_sum,
                            query(0, n - 1, x, y, 0, aint2).max_sum)
                << '\n';
    }
  }
}
