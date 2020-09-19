/*
  Implments graph ADS.
*/

#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <time.h>
#include "util.h"

using namespace std;

class Node {
  public:
    double value;
    int id;
    Node(double value):value(value){
      this -> id = this -> count++;
    };
    friend ostream & operator << (ostream& os, Node& n){
      os << " (" << n.id << ", " << n.value << ") ";
      return os;
    };

  private:
    static int count;
};

int Node::count = 0;

class Edge {
  public:
    Node* from;
    Node* to;
    double value;
    Edge(double value, Node* from, Node* to):
      value(value), from(from), to(to) {};
    friend ostream & operator << (ostream& os, Edge& l){
      os << " (" << l.from -> id << " -> "
         << l.to -> id << ", " << l.value << ")";
      return os;
    };
};

class Graph {
  public:
    int _num_edges;
    int _num_nodes;
    vector<Node> nodes;
    vector<Edge> edges;

    Graph():_num_edges(0), _num_nodes(0){
      srand(time(0));

      vector<Node>* nodes_ptr = new vector<Node>();
      this -> nodes = *nodes_ptr;

      vector<Edge>* edges_ptr = new vector<Edge>();
      this -> edges = *edges_ptr;
    };

    void make_random_graph(int n,
      double nv_range_low,
      double nv_range_high,
      double ev_range_low,
      double ev_range_high,
      double cprob)
    {
      double random;
      for (int i=0;i<n;i++){
        random = get_random(
          nv_range_low,
          nv_range_high
        );
        this -> add_node(random);
      }
      for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
          if (i != j) {
            random = get_random(0.0, 1.0);
            if (random < cprob){
              random = get_random(
                ev_range_low,
                ev_range_high
              );
              this -> add_edge(
                random,
                &(this -> nodes[i]),
                &(this -> nodes[j])
              );
            }
          }
        }
      }
    };

    int N() {
      return this -> nodes.size();
    };

    int E() {
      return this -> edges.size();
    };

    void add_node(double value){
      Node* new_node_ptr = new Node(value);
      Node new_node = *new_node_ptr;
      this -> nodes.push_back(new_node);
    };

    void add_edge(double value, Node* from, Node* to){
      Edge* edge_ptr = new Edge(value, from, to);
      this -> edges.push_back(*edge_ptr);
    };

    Node get_node(int i) {
      return this -> nodes[i];
    };

    Edge get_edge(int i) {
      return this -> edges[i];
    };

    double get_node_value(int i) {
      if (i >= 0 && i < this -> N()){
        return this -> nodes[i].value;
      } else {
        throw "Node Index out of bounds";
      }
    }

    void set_node_value(int i, double value) {
      if (i >= 0 && i < this -> N()){
        this -> nodes[i].value = value;
      } else {
        throw "Node Index out of bounds";
      }
    }

    double get_edge_value(int i) {
      if (i >= 0 && i < this -> E()){
        return this -> edges[i].value;
      } else {
        throw "Edge Index out of bounds";
      }
    }

    void set_edge_value(int i, double value) {
      if (i >= 0 && i < this -> E()){
        this -> edges[i].value = value;
      } else {
        throw "Edge Index out of bounds";
      }
    }

    void delete_edge(int i) {
      if (i >= 0 && i < this -> E()) {
        this -> edges.erase (this -> edges.begin() + i);
      } else {
        throw "Edge Index out of bounds";
      }
    }

    int adjacent(Node* n, Node* m){
      for (auto edge:this->edges)
        if ((edge.to == n && edge.from == m)
            || (edge.to == m && edge.from == n))
              return 1;
      return 0;
    };

    vector<Node*> neighbors(Node* n){
      vector<Node*> neighbor_nodes;
      for (auto edge:this->edges){
        if (edge.to -> id == n -> id)
          neighbor_nodes.push_back(edge.from);
        if (edge.from -> id == n -> id)
          neighbor_nodes.push_back(edge.to);
      }
      return neighbor_nodes;
    };

    double distance(Node* n, Node* m) {
      for (auto edge:this -> edges)
        if ((edge.from -> id == n -> id && edge.to -> id == m -> id)
          || (edge.to -> id == n -> id && edge.from -> id == m -> id))
            return edge.value;
    };

    friend ostream & operator << (ostream& os, Graph& g){
      cout << g.N() << " Nodes: ";
      for (auto node:g.nodes)
        os << node;
      cout << endl;
      cout << g.E() << " Edges: ";
      for (auto edge:g.edges)
        os << edge;
      cout << endl;
      return os;
    };
};

#endif /* GRAPH_H */
