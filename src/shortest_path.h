/*
  file: shortest_path.h

	implementation of dijkstras algorithm. ShortestPath takes a Graph object, a
	start and an end point. It creates a PriorityQueue instance and adds the
	start node. It then looks at all neighbors of the start node and chooses
	the one the least distance from it. In doing so it places it in the set of
	node we know the shortest distance to. We iterate by looking at all of this
	nodes neighbors choosing again the one with the shortest distance that
	hasn't been visited yet. By iterating on this we eventually either exahaust
	all possible routes or get to the final node.
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

		struct Result make_result(int outcome, QueueItem* end_point, Node* t) {
			struct Result result;
			if (!outcome) {
				result.success = 0;
				return result;
			};
			double total_score = end_point -> score;
			vector<Node*> path;
			do {
				path.push_back(end_point -> node);
			} while ((end_point = end_point -> prev) != NULL);
			reverse(path.begin(), path.end());
			result.path = path;
			result.score = total_score;
			result.success = 1;
			return result;
		};

  public:
    ShortestPath(Graph* g):G(g){};
		~ShortestPath(){
			delete open;
		};
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
      return make_result(finished, end_point, t);
    }
};

#endif /* SHORTEST_PATH_H */
