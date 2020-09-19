/*
  file: shortest_path.h

  As we construct the candidates for the shortest path we construct a Path Tree
  that stores by reference the current node and the node from which the Path
  travelled. This way when we start from the terminal node and follow each
  parent until we get to the start node.
*/

#ifndef SHORTEST_PATH_H
#define SHORTEST_PATH_H

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <time.h>
#include <algorithm>
#include "util.h"
#include "graph.h"
#include "priority_queue.h"

using namespace std;

struct compare
{
	Node const* key;
	compare(Node const* n): key(n) { }

	bool operator()(Node const* i)
	{
		return (i -> id == key -> id);
	}
};

struct Result {
	vector<Node*> path;
	double score;
	int success;
};

class ShortestPath {
  private:
    PriorityQueue* open;
    vector<Node*> closed;
    Graph* G;

		struct Result make_result(QueueItem* end_point, Node* t) {
			struct Result result;

			int success = end_point -> node -> id == t -> id ? 1 : 0;
			if (success) {
				double total_score = end_point -> score;
				vector<Node*> path;
				do {
					path.push_back(end_point -> node);
				} while ((end_point = end_point -> prev) != NULL);
				result.path = path;
				result.score = total_score;
			}
			result.success = success;
			return result;
		}

  public:
    ShortestPath(Graph* g):G(g){};

    struct Result path(Node* s, Node* t){
      open = new PriorityQueue(s);
      Node* current_node;
      double dist;
			int finished = 0;
			QueueItem* end_point;

			while (!open -> is_empty() && !finished){
				current_node = open -> top() -> node;
				if (current_node -> id == t -> id){
					end_point = open -> top();
					finished = 1;
				}

				vector<Node*> neighbors = this -> G -> neighbors(current_node);
        for (auto neighbor:neighbors) {
          if (none_of(closed.begin(), closed.end(), compare(neighbor))) {
            dist = G -> distance(current_node, neighbor);
            open -> update(neighbor, dist);
          }
        }
        closed.push_back(current_node);
        this -> open -> pop();
      }

      return make_result(end_point, t);
    }
};

#endif /* SHORTEST_PATH_H */
