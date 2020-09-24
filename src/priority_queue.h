/*
  file: priority_queue.h
  Implement a PriorityQueue min heap.

  classes: QueueItem and PriorityQueue.

  PriorityQueue implementation reference:
    https://www.techiedelight.com/min-heap-max-heap-implementation-c/

  Note: QueueItem contains a node and a reference, prev, to the previous
  QueueItem that containes the last node in the path that makes up the score
  value. At the end of the computation the algorithm knows the shortest path
  by following the sequence of prev references till the NULL value.
*/

#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <time.h>
#include "util.h"
#include "graph.h"

using namespace std;

class QueueItem {
  public:
    double score;
    Node* node;
    QueueItem* prev;
    QueueItem(Node* node, QueueItem* prev, double score):
        node(node), prev(prev), score(score) {};

    int update(double new_score, QueueItem* new_prev) {
      /*
        If a new path is found to the node in this queue item then we update
        its score and change the previous node.
      */

      if (new_score < this -> score){
        this -> prev = new_prev;
        this -> score = new_score;
        return 1;
      }
      return 0;
    }
};

class PriorityQueue {
  private:
    int left(int i){
      return 2*i + 1;
    }
    int right(int i){
      return 2*i + 2;
    }
    int parent(int i){
      return (i - 1) / 2;
    }
    void heapify_up(int i){
      /*
        Get the parent index. If the parent score is greater than the child
        score swap and recursivly call heapify_up on the parent index now with
        the child value in it's place. This means the smalles value rises to
        the top of the heap.
      */
      int parent_i = parent(i);
      if(items[parent_i] -> score > items[i] -> score) {
        swap(items[parent_i], items[i]);
        this -> heapify_up(parent_i);
      }
    }

    void heapify_down(int i){
      /*
        Replace the root element with the last element in the heap. We then
        swap that element with the smallest of each of it's children and so on
        recursivly until it's the smallest element in the heap.
      */
      int left_child_i = left(i);
      int right_child_i = right(i);
      int smallest = i;

      if (left_child_i < items.size()
          && items[left_child_i] -> score < items[smallest] -> score)
        smallest = left_child_i;

      if (right_child_i < items.size()
          && items[right_child_i] -> score < items[left_child_i] -> score)
        smallest = right_child_i;

        if (smallest != i){
          swap(items[i], items[smallest]);
          heapify_down(smallest);
        }
    }


  public:
    vector<QueueItem*> items;
    PriorityQueue(Node* inital_node){
      QueueItem* item = new QueueItem(inital_node, NULL, 0);
      items.push_back(item);
    };
    ~PriorityQueue(){
      for (auto item:items)
        delete item;
    }

    int is_empty(){
      return items.size() == 0;
    }

    void update(Node* node, double d) {
      /*
        If node already in PQ then we want to know if the path that's
        currently at the top item in the queue is better than the path we have
        to that node already.

        If node in PQ already we update that queue item. Update on
        QueueItem returns 1 if any changes are made in which case we
        run heapify_down to account for the case that the change made to
        that queue item has broken the min heap property.

        If the node doesn't match with a node already in the PQ then we insert
        a new QueueItem with previosu QueueItem equal to the top QueueItem.
      */

      double new_score = d + this -> top() -> score;
      for (auto item:items)
        if (node -> id == item -> node -> id) {
          if (item -> update(new_score, this -> top()))
            this -> heapify_down(0);
            return;
        }

      this -> insert(node, new_score, this -> top());
      return;
    }

    void insert(Node* node, double score, QueueItem* prev){
      QueueItem* item = new QueueItem(node, prev, score);
      items.push_back(item);
      this -> heapify_up(items.size() - 1);
    }

    void pop(){
      this -> items[0] = this -> items.back();
      this -> items.pop_back();
      this -> heapify_down(0);
    }

    QueueItem* top(){
      return items[0];
    }
};

#endif /* PRIORITY_QUEUE_H */
