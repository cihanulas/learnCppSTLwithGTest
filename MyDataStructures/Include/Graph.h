#pragma once

#include <string>
#include <unordered_map>
//
// class GNode {
//  size_t id;
//  std::string data;
//};
namespace Graph {
using NodeWeightMap =
    std::unordered_map<std::string /*to_node*/, double /*weight*/>;
}

struct IGraph {
  virtual bool addVertex(const std::string& node) = 0;
  virtual bool addEdge(const std::string& from, const std::string& to,
                       double weight) = 0;
  virtual bool IsVertexExist(const std::string& node) const = 0;
  virtual Graph::NodeWeightMap find(const std::string& node) = 0;
};

class DirectedGraph : public IGraph {
 public:
  using NodeWeightMap = Graph::NodeWeightMap;
  bool addVertex(const std::string& node) override;
  bool virtual addEdge(const std::string& node1, const std::string& node2,
                       double weight) override;
  bool IsVertexExist(const std::string& node) const override;
  NodeWeightMap find(const std::string& node) override {
    auto it = m_node_connections.find(node);
    if (it == m_node_connections.end()) return NodeWeightMap{};
    return it->second;
  }

 private:
  bool _addEdge(const std::string& node1, const std::string& node2,
                double weight) {
    auto it = m_node_connections.find(node1);
    if (it == m_node_connections.end()) {
      addVertex(node1);
      m_node_connections.at(node1).emplace(node2, weight);
    } else {
      it->second.emplace(node2, weight);
    };
    return true;
  };

  /*
  node1 - 100 - node2
  node1 - 200 - node3
  */

  // Node -> connections map

  std::unordered_map<std::string /*node_from*/, NodeWeightMap>
      m_node_connections;
};

bool DirectedGraph::addVertex(const std::string& node) {
  // insert the node, if there are already the new one will be ignored.
  m_node_connections.emplace(node, NodeWeightMap{});
  return true;
};

bool DirectedGraph::addEdge(const std::string& node1, const std::string& node2,
                            double weight = 1) {
  _addEdge(node1, node2, weight);
  return true;
};

bool DirectedGraph::IsVertexExist(const std::string& node) const {
  return m_node_connections.find(node) != m_node_connections.end();
}

class UnDirectedGraph : public DirectedGraph {
 public:
  bool addEdge(const std::string& node1, const std::string& node2,
               double weight) override;
};

bool UnDirectedGraph::addEdge(const std::string& node1,
                              const std::string& node2, double weight) {
  DirectedGraph::addEdge(node1, node2, weight);
  DirectedGraph::addEdge(node2, node1, weight);
  return true;
}
