#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

#include "map.h"
using namespace std;
template<typename K, typename V>
class BstMap : public Map<K, V> {
 private:
  class Node {
   public:
    K key;
    V value;
    Node * left;
    Node * right;

   public:
    Node(K k, V v) : key(k), value(v), left(NULL), right(NULL) {}
  };
  Node * root;

  void getNode(Node * curr);
  void mapFree(Node * curr);

 public:
  BstMap() : root(NULL) {}
  BstMap(const BstMap<K, V> & rhs);
  BstMap & operator=(const BstMap<K, V> & rhs);
  virtual void add(const K & k, const V & v);
  virtual const V & lookup(const K & k) const throw(std::invalid_argument);
  virtual void remove(const K & k);
  virtual ~BstMap();
};

template<typename K, typename V>
void BstMap<K, V>::getNode(Node * curr) {
  if (curr != NULL) {
    this->add(curr->key, curr->value);
    getNode(curr->left);
    getNode(curr->right);
  }
}

template<typename K, typename V>
BstMap<K, V>::BstMap(const BstMap<K, V> & rhs) : root(NULL) {
  getNode(rhs.root);
}

template<typename K, typename V>
BstMap<K, V> & BstMap<K, V>::operator=(const BstMap<K, V> & rhs) {
  if (this != &rhs) {
    BstMap<K, V> temp(rhs);
    std::swap(root, temp.root);
  }
  return *this;
}

template<typename K, typename V>
void BstMap<K, V>::add(const K & k, const V & v) {
  Node ** curr = &root;
  while (*curr != NULL) {
    if (k < (*curr)->key) {
      curr = &(*curr)->left;
    }
    else if (k > (*curr)->key) {
      curr = &(*curr)->right;
    }
    else {
      (*curr)->value = v;
      return;
    }
  }
  *curr = new Node(k, v);
}

template<typename K, typename V>
const V & BstMap<K, V>::lookup(const K & k) const throw(std::invalid_argument) {
  Node * curr = root;
  while (curr != NULL) {
    if (k == curr->key) {
      return curr->value;
    }
    else if (k < curr->key) {
      curr = curr->left;
    }
    else {
      curr = curr->right;
    }
  }

  throw std::invalid_argument("Cannot find the key!!!");
}

template<typename K, typename V>
void BstMap<K, V>::remove(const K & k) {
  Node ** curr = &root;
  while (*curr != NULL) {
    if (k < (*curr)->key) {
      curr = &(*curr)->left;
    }
    else if (k > (*curr)->key) {
      curr = &(*curr)->right;
    }
    else {
      if ((*curr)->left == NULL) {
        Node * temp = (*curr)->right;
        delete *curr;
        *curr = temp;
      }
      else if ((*curr)->right == NULL) {
        Node * temp = (*curr)->left;
        delete *curr;
        *curr = temp;
      }
      else {
        Node * prev = *curr;
        Node * temp = (*curr)->right;
        bool goLeft = false;
        while (temp->left != NULL) {
          prev = temp;
          temp = temp->left;
          goLeft = true;
        }
        temp->left = (*curr)->left;
        if (goLeft) {
          prev->left = temp->right;
          temp->right = (*curr)->right;
        }
        delete *curr;
        *curr = temp;
      }
      return;
    }
  }
}

template<typename K, typename V>
void BstMap<K, V>::mapFree(Node * curr) {
  if (curr != NULL) {
    mapFree(curr->left);
    mapFree(curr->right);
    delete curr;
  }
}

template<typename K, typename V>
BstMap<K, V>::~BstMap() {
  mapFree(root);
}
