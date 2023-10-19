#ifndef CPL_UTIL_GRAPH_H
#define CPL_UTIL_GRAPH_H

#include <map>
#include <set>
#include <unordered_map>

namespace cpl::util {

template <typename NodeT>
class Graph {
  using node_ptr_t = NodeT *;
  using node_id_t = unsigned;

 public:
  Graph();

  void add_edge(node_ptr_t from, node_ptr_t to);

 private:
  bool maybe_add_node(node_ptr_t np);

 private:
  std::unordered_map<node_ptr_t, node_id_t> ids_by_node_;
  std::map<node_id_t, std::set<node_id_t>> g_;
};

template <typename T>
void topological_sort(Graph<T> &g);

}  // namespace cpl::util

#endif  // CPL_UTIL_GRAPH_H