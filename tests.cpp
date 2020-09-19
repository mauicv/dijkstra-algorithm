/*
  file: tests.cpp
  Test cases
*/

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <time.h>
#include <cassert>

#include "src/graph.h"
#include "src/priority_queue.h"
#include "src/shortest_path.h"

void test_1();
void test_2();
void test_3();
void test_4();
void test_5();


int main(){
  vector<void (*)()> tests = {
    // *test_1,
    // *test_2,
    // *test_3,
    // *test_4,
    *test_5
  };

  for (auto test:tests) test();
  return 0;
};


/*
  Case 1:
    Create graph, Add nodes, get nodes, check nodes adjacent, add edge,
    check nodes adjecent, check distance between nodes, check edge value,
    check node has one neighbor.
*/

void test_1(){
  Graph g = Graph();
  g.add_node(1);
  g.add_node(2);
  Node n1 = g.get_node(0);
  Node n2 = g.get_node(1);
  assert(!g.adjacent(&n1, &n2));
  assert(g.neighbors(&n1).size() == 0);
  g.add_edge(1.0, &n1, &n2);
  assert(g.adjacent(&n1, &n2));
  assert(g.distance(&n1, &n2) == 1.0);
  assert(g.get_edge_value(0) == 1.0);
  assert(g.neighbors(&n1).size() == 1);
}

/*
  Case 2:
    Create random graph. Verify node values and edge values are in correct
    range.
*/

void test_2(){
  Graph g = Graph();
  g.make_random_graph(10, 0.3, 1.7, 0.0, 10.0, 0.1);
  assert(g.nodes.size() == 10);
  for (auto node:g.nodes)
    assert(0.3 < node.value && 1.7 > node.value);
  for (auto edge:g.edges)
    assert(0.0 < edge.value && 10.0 > edge.value);
}

/*
  Case 3:
    Check priority_queue implementation.
*/

void test_3(){
  Graph g = Graph();
  for (int i=0; i<10; i++)
    g.add_node(0);
  Node n = g.get_node(0);
  PriorityQueue pq = PriorityQueue(&n);
  pq.pop();

  double test_values[5] = {5.4, 6.7, 3.2, 9.1, 0.2};
  double values_exp[5] = {5.4, 5.4, 3.2, 3.2, 0.2};

  for (int i=0; i<5; i++){
    Node n = g.get_node(i);
    pq.insert(&n, test_values[i], pq.top());
    assert(pq.top() -> score == values_exp[i]);
  }

  pq.pop();
  assert(pq.top() -> score == 3.2);
}

/*
  Case 4:
    Check dijkstras algorithm on known simple graph.
*/

void test_4(){
  Graph g = Graph();
  g.add_node(0);
  g.add_node(0);
  g.add_node(0);
  g.add_node(0);
  g.add_node(0);
  g.add_node(0);

  Node n1 = g.get_node(0);
  Node m1 = g.get_node(1);
  g.add_edge(1.0, &n1, &m1);

  Node n2 = g.get_node(1);
  Node m2 = g.get_node(2);
  g.add_edge(1.0, &n2, &m2);

  Node n3 = g.get_node(0);
  Node m3 = g.get_node(3);
  g.add_edge(2.0, &n3, &m3);

  Node n4 = g.get_node(3);
  Node m4 = g.get_node(4);
  g.add_edge(4.0, &n4, &m4);

  Node n5 = g.get_node(0);
  Node m5 = g.get_node(5);
  g.add_edge(3.0, &n5, &m5);

  Node n6 = g.get_node(5);
  Node m6 = g.get_node(4);
  g.add_edge(1.0, &n6, &m6);

  Node s = g.get_node(0);
  Node t = g.get_node(4);

  ShortestPath spa = ShortestPath(&g);
  Result result = spa.path(&s, &t);

  assert(result.success == 1);
  assert(result.score == 4.0);
  int node_ids[3] = {4, 5, 0};
  for (int i = 0; i<result.path.size(); i++)
    assert(result.path[i] -> id == node_ids[i]);
}

/*
  Case 5:
    Check dijkstras algorithm fails on known simple disconnected graph.
*/

void test_5(){
  Graph g = Graph();
  g.add_node(0);
  g.add_node(0);
  g.add_node(0);

  Node n1 = g.get_node(0);
  Node n2 = g.get_node(1);
  Node n3 = g.get_node(2);
  g.add_edge(1.0, &n1, &n2);

  ShortestPath spa = ShortestPath(&g);
  Result result = spa.path(&n1, &n3);

  // assert(result.success == 1);
  // assert(result.score == 4.0);
  // int node_ids[3] = {4, 5, 0};
  // for (int i = 0; i<result.path.size(); i++)
  //   assert(result.path[i] -> id == node_ids[i]);
}
