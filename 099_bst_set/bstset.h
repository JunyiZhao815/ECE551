#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

#include "set.h"

using namespace std;

template<typename T>
class BstSet : public Set<T> {
 private:
  class Node {
   public:
    T key;
    Node * left;
    Node * right;
    Node(T k) : key(k), left(NULL), right(NULL) {}
  };
  Node * root;

  void getNode(Node * curr);
  void setFree(Node * curr);

 public:
  BstSet<T>() : root(NULL) {}
  BstSet<T>(const BstSet<T> & rhs);
  BstSet<T> & operator=(const BstSet<T> & rhs);
  virtual void add(const T & k);
  virtual bool contains(const T & k) const;
  virtual void remove(const T & k);
  virtual ~BstSet<T>();
};

template<typename T>
void BstSet<T>::getNode(Node * curr) {
  if (curr != NULL) {
    this->add(curr->key);
    getNode(curr->left);
    getNode(curr->right);
  }
}

template<typename T>
BstSet<T>::BstSet(const BstSet<T> & rhs) : root(NULL) {
  getNode(rhs.root);
}

template<typename T>
BstSet<T> & BstSet<T>::operator=(const BstSet<T> & rhs) {
  if (this != &rhs) {
    BstSet<T> temp(rhs);
    std::swap(root, temp.root);
  }
  return *this;
}

template<typename T>
void BstSet<T>::add(const T & k) {
  Node * curr = root;
  while (curr != NULL) {
    if (k < curr->key) {
      curr = curr->left;
    }
    else if (k > curr->key) {
      curr = curr->right;
    }
    else {
      return;
    }
  }
  curr = new Node(k);
}

template<typename T>
bool BstSet<T>::contains(const T & k) const {
  Node * curr = root;
  while (curr != NULL) {
    if (k == curr->key) {
      return true;
    }
    else if (k < curr->key) {
      curr = curr->left;
    }
    else {
      curr = curr->right;
    }
  }
  return false;
}

template<typename T>
void BstSet<T>::remove(const T & k) {
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

template<typename T>
void BstSet<T>::setFree(Node * curr) {
  if (curr != NULL) {
    setFree(curr->left);
    setFree(curr->right);
    delete curr;
    curr = NULL;
  }
}

template<typename T>
BstSet<T>::~BstSet() {
  setFree(root);
}
