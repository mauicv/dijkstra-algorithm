/*

  TODO:
    - add delete methods
    - override equlity operator for nodes and edges
*/

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <time.h>
#include "src/graph.h"
#include "src/priority_queue.h"
#include "src/shortest_path.h"


int main(void){
  Graph g = Graph();
  g.make_random_graph(50, 0.3, 1.7, 0.0, 10.0, 0.025);

  Node n1 = g.get_node(0);
  Node n2 = g.get_node(9);

  cout << "Computing path from: " << n1 << " -> " << n2 << endl;

  ShortestPath spa = ShortestPath(&g);
  Result result = spa.path(&n1, &n2);

  if (result.success) {
    cout << "score: " << result.score << endl;
    cout << "path: ";
    for (auto node:result.path)
      cout << *node;
    cout << endl;
  } else {
    cout << "No path found.";
  }
}
