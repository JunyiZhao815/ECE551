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
    std::pair<K, V> val;
    Node() : left(NULL), right(NULL) {}
    Node(const K & key, const V & value) : left(NULL), right(NULL), val(key, value) {}
  };
  Node * root;

 public:
  BstMap() : root(NULL) {}
  virtual ~BstMap<K, V>() { freeTree(root); }
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
        if (key < travesal->val.first) {
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
      if (travesal->val.first == key) {
        return travesal->val.second;
      }
      else if (travesal->val.first > key) {
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
  Node * deleteNode(Node * root, K key) {
    if (root == NULL) {
      return NULL;
    }
    if (key < root->val.first) {
      root->left = deleteNode(root->left, key);
    }
    else if (key > root->val.first) {
      root->right = deleteNode(root->right, key);
    }
    else {
      if (root->left == NULL and root->right == NULL) {
        return NULL;
      }
      else if (root->left == NULL) {
        Node * tmp = root->right;
        delete root;
        return tmp;
      }
      else if (root->right == NULL) {
        Node * tmp = root->left;
        delete root;
        return tmp;
      }
      Node * temp = getMin(root->right);
      root->val.first = temp->val.first;

      root->right = deleteNode(root->right, temp->val.first);
    }
    return root;
  }
};
