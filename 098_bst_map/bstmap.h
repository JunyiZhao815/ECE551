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
  virtual ~BstMap<K, V>() {}
  virtual void add(const K & key, const V & value) {
    if (root == NULL) {
      root = new Node(key, value);
    }
    else {
      Node * travesal = root;
      while (true) {
        if (key > travesal->key) {
          if (travesal->right == NULL) {
            travesal->right = new Node(key, value);
            break;
          }
          else {
            travesal = travesal->right;
          }
        }
        else {
          if (travesal->left == NULL) {
            travesal->left = new Node(key, value);
            break;
          }
          else {
            travesal = travesal->left;
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
    throw std::invalid_argument("Cannot find the key");
  }
  virtual void remove(const K & key) { root = helper(root, key); }
  Node * helper(Node * curr, const K & key) {
    if (curr == NULL) {
      return curr;
    }
    if (curr->key == key) {
      if (curr->left == NULL) {
        Node * temp = curr->right;
        delete temp;
        return temp;
      }
      else if (curr->right == NULL) {
        Node * temp = curr->left;
        delete curr;
        return temp;
      }
      else {
        K k = getMinKey(curr->right);
        V v = lookup(k);
        curr->right = helper(curr->right, k);
        curr->key = k;
        curr->value = v;
        return curr;
      }
    }
    else if (key < curr->key) {
      curr->left = helper(curr->left, key);
      return curr;
    }
    else {
      curr->right = helper(curr->right, key);
      return curr;
    }
  }
  K getMinKey(Node * curr) {
    if (curr == NULL) {
      std::cerr << "cannot get the minimize key!" << std::endl;
      exit(EXIT_FAILURE);
    }
    Node * travesal = curr;
    K temp = curr->key;
    while (travesal != NULL) {
      temp = travesal->key;
      travesal = travesal->left;
    }
    return temp;
  }
};
