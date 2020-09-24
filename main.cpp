/*
  main:

  creates a random graph. Selects node 0 and then iterates throught the
  rest of the nodes counting the number of connected paths that exist and
  there scores. Finally outputs the average length of path.
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
  Graph* g_ptr = new Graph();
  Graph g = *g_ptr;
  g.make_random_graph(50, 1.0, 1.0, 1.0, 10.0, 0.4);
  Node n1 = g.get_node(0);
  Node n2 = Node(0);
  Result result;
  double sum = 0, count = 0;
  ShortestPath* spa;
  for (int i=1; i<=50; i++){
    spa = new ShortestPath(&g);
    n2 = g.get_node(i);
    result = spa -> path(&n1, &n2);
    delete spa;
    if (result.success) {
      sum += result.path.size();
      count++;
    }
  }
  delete g_ptr;

  cout << endl;
  cout << "Total connected nodes to first node:\t" << count << endl;
  cout << "Average size of path:\t\t\t" << sum/count << endl;
  cout << endl;
}
