#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "map.h"
template<typename K, typename V>
class BstMap : public Map<K, V> {
  class Node {
   public:
    Node * left;
    Node * right;
    K key;
    V value;
    Node() : left(NULL), right(NULL) {}
    Node(const K & key, const V & value) :
        left(NULL), right(NULL), key(key), value(value) {}
  };
  Node * root;

 public:
  BstMap() : root(NULL) {}
  virtual ~BstMap<K, V>() {}  // { freeTree(root); }
  void freeTree(Node * root) {
    if (root == NULL) {
      return;
    }
    freeTree(root->left);
    freeTree(root->right);
    delete root;
  }
  virtual void add(const K & key, const V & value) {
    //base case
    if (root == NULL) {
      root = new Node(key, value);
    }
    else {
      Node * travesal = root;
      while (travesal != NULL) {
        if (key < travesal->key) {
          if (travesal->left == NULL) {
            travesal->left = new Node(key, value);
            break;
          }
          else {
            travesal = travesal->left;
          }
        }
        else {
          if (travesal->right == NULL) {
            travesal->right = new Node(key, value);
            break;
          }
          else {
            travesal = travesal->right;
          }
        }
      }
    }
  }
  virtual const V & lookup(const K & key) const throw(std::invalid_argument) {
    Node * travesal = root;
    while (travesal != NULL) {
      if (travesal->key == key) {
        return travesal->value;
      }
      else if (travesal->key > key) {
        travesal = travesal->left;
      }
      else {
        travesal = travesal->right;
      }
    }
    throw std::invalid_argument("Cannot find the key!");
  }
  Node * getMin(Node * root) {
    Node * curr = root;
    while (curr != NULL && curr->left != NULL) {
      curr = curr->left;
    }
    return curr;
  }
  virtual void remove(const K & key) { root = deleteNode(root, key); }
  Node * deleteNode(Node * curr, K key) {
    if (curr == NULL) {
      return NULL;
    }
    if (key < curr->key) {
      curr->left = deleteNode(curr->left, key);
    }
    else if (key > curr->key) {
      curr->right = deleteNode(curr->right, key);
    }
    else {
      if (curr->left == NULL and curr->right == NULL) {
        return NULL;
      }
      else if (curr->left == NULL) {
        Node * tmp = curr->right;
        delete curr;
        return tmp;
      }
      else if (curr->right == NULL) {
        Node * tmp = curr->left;
        delete curr;
        return tmp;
      }
      else {
        Node * t = getMin(root->right);
        K k = t->key;
        V v = t->value;
        root->right = deleteNode(curr->right, k);
        root->key = k;
        root->value = v;
        return curr;
      }
    }
  };
};
