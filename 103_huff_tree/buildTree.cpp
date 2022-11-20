#include "node.h"
using namespace std;
Node * buildTree(uint64_t * counts) {
  //WRITE ME!
  priority_queue<Node *, vector<Node *>, NodePtrCompare> priority_queue_t;
  for (int i = 0; i < 257; i++) {
    if (counts[i] != 0) {
      priority_queue_t.push(new Node(i, counts[i]));
    }
  }
  while (priority_queue_t.size() > 1) {
    Node * first = priority_queue_t.top();
    priority_queue_t.pop();
    Node * second = NULL;
    if (!priority_queue_t.empty()) {
      second = priority_queue_t.top();
      priority_queue_t.pop();
    }
    priority_queue_t.push(new Node(first, second));
  }
  return priority_queue_t.top();
}
