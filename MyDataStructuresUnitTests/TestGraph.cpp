#include "pch.h"

#include "Graph.h"
#include "gmock\gmock.h"

MATCHER_P(GraphHasNode, value, "Is Vertex Exist in the Graph") {
  bool res = arg.IsVertexExist(value);
  return res;
}

MATCHER_P2(NodeRelation, node, linked_nodes, "Check Node Relations") {
  Graph::NodeWeightMap it = arg.find(node);
  return true;  // it == linked_nodes;
}

void AddEdges(IGraph& graph) {
  graph.addEdge("0", "1", 1);
  graph.addEdge("0", "2", 1);

  graph.addEdge("1", "2", 2);
  graph.addEdge("1", "3", 2);

  graph.addEdge("2", "3", 3);
  graph.addEdge("3", "0", 4);
}

/*
  Create a graph with directed edge:
  0: 1,2
  1: 2,3
  2: 1
  3: 0
*/
void CheckDirectedGraph(IGraph& graph) {
  Graph::NodeWeightMap node0Edges{{"1", 1}, {"2", 1}};
  Graph::NodeWeightMap node1Edges{{"2", 2}, {"3", 2}};
  Graph::NodeWeightMap node2Edges{{"3", 3}};
  Graph::NodeWeightMap node3Edges{{"0", 4}};

  EXPECT_EQ(graph.find("0"), node0Edges);
  EXPECT_EQ(graph.find("1"), node1Edges);
  EXPECT_EQ(graph.find("2"), node2Edges);
  EXPECT_EQ(graph.find("3"), node3Edges);
}

/*
  Create a graph like:
  0: 1,2,3
  1: 0,2,3
  2: 0,1,3
  3: 0,1,2
*/

void CheckUndirectedGraph(IGraph& graph) {
  Graph::NodeWeightMap node0Edges{{"1", 1}, {"2", 1}, {"3", 4}};
  Graph::NodeWeightMap node1Edges{{"0", 1}, {"2", 2}, {"3", 2}};
  Graph::NodeWeightMap node2Edges{{"0", 1}, {"1", 2}, {"3", 3}};
  Graph::NodeWeightMap node3Edges{{"0", 4}, {"1", 2}, {"2", 3}};

  EXPECT_EQ(graph.find("0"), node0Edges);
  EXPECT_EQ(graph.find("1"), node1Edges);
  EXPECT_EQ(graph.find("2"), node2Edges);
  EXPECT_EQ(graph.find("3"), node3Edges);
}

TEST(TestGraph, AddVertex) {
  // Use initializer list
  DirectedGraph graph;
  graph.addVertex("0");
  graph.addVertex("1");
  ASSERT_THAT(graph, GraphHasNode("0"));
  ASSERT_THAT(graph, GraphHasNode("1"));
  EXPECT_FALSE(graph.IsVertexExist("2"));
}

// Directed Edge Tests
TEST(TestGraph, AddDirectedEdgesWithVertexInitialization) {
  DirectedGraph graph;
  graph.addVertex("0");
  graph.addVertex("1");
  graph.addVertex("2");
  graph.addVertex("3");
  AddEdges(graph);
  CheckDirectedGraph(graph);
}
TEST(TestGraph, AddDirectedEdgesWithoutVertexInitialization) {
  DirectedGraph graph;
  AddEdges(graph);
  CheckDirectedGraph(graph);
}

// Undirected Edge Tests
TEST(TestGraph, AddUnDirectedEdgesWithVertexInitialization) {
  /*
    Create a graph like:
    0: 1,2,3
    1: 0,2,3
    2: 0,1,3
    3: 0,1,2
  */

  UnDirectedGraph graph;
  graph.addVertex("0");
  graph.addVertex("1");
  graph.addVertex("2");
  graph.addVertex("3");
  AddEdges(graph);
  CheckUndirectedGraph(graph);
}

TEST(TestGraph, AddUnDirectedEdgesWithoutVertexInitialization) {
  UnDirectedGraph graph;
  AddEdges(graph);
  CheckUndirectedGraph(graph);
}
