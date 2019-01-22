#include <iostream>

#include "node.h"
Node * buildTree(uint64_t * counts) {
  priority_queue_t pq;
  for (unsigned i = 0; i < 257; i++) {
    if (counts[i] != 0) {
      pq.push(new Node(i, counts[i]));
    }
  }
  while (pq.size() > 1) {
    Node * top1 = pq.top();
    pq.pop();  //dequeue first element

    Node * top2 = pq.top();
    pq.pop();  //dequeue second element

    Node * parent = new Node(top1, top2);  //LEAK OCCURS HERE
    pq.push(parent);
  }
  return pq.top();
}
