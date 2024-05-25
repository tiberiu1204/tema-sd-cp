#include <fstream>
#include <iostream>
#include <set>

std::ifstream in("proc2.in");
std::ofstream out("proc2.out");

int main() {
  int n, m;
  in >> n >> m;
  std::set<int> procs;
  for (int i = 1; i <= n; i++) {
    procs.insert(i);
  }
  std::multiset<std::pair<int, int>>
      queue_heap; // first = next available Ti, second = proc_id
  for (int i = 0; i < m; i++) {
    int start, duration;
    in >> start >> duration;
    while (!queue_heap.empty() && queue_heap.begin()->first <= start) {
      procs.insert(queue_heap.begin()->second);
      queue_heap.erase(queue_heap.begin());
    }
    int proc_id = *procs.begin();
    procs.erase(procs.begin());
    queue_heap.insert(std::make_pair(start + duration, proc_id));
    out << proc_id << '\n';
  }
}
