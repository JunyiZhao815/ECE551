#include <assert.h>

#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "map.h"

template<typename K, typename V>
class BstMap : public Map<K, V> {
 private:
  class Node {
   public:
    K key;
    V value;
    Node * left;
    Node * right;
    Node(K key, V value) : key(key), value(value), left(NULL), right(NULL) {}
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
    if (root == NULL) {
      root = new Node(key, value);
    }
    else {
      Node * travesal = root;
      while (travesal != NULL) {
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
  Node * findNode(Node * curr, const K & key) {
    Node * travesal = curr;
    while (travesal != NULL) {
      if (key == travesal->key) {
        return travesal;
      }
      else if (key > travesal->key) {
        travesal = travesal->right;
      }
      else {
        travesal = travesal->left;
      }
    }
    return travesal;
  }

  virtual const V & lookup(const K & key) const throw(std::invalid_argument) {
    Node * target = findNode(this->root, key);
    if (target == NULL) {
      throw std::invalid_argument("key not found");
    }
    else {
      return target->value;
    }
  }
  /**
  virtual const V & lookup(const K & key) const throw(std::invalid_argument) {
    Node * travesal = this->root;
    Node * target = NULL;
    while (travesal != NULL) {
      if (key == travesal->key) {
        target = travesal;
      }
      else if (key < travesal->key) {
        travesal = travesal->left;
      }
      else {
        travesal = travesal->right;
      }
    }
    if (target == NULL) {
      throw std::invalid_argument("cannot find the key");
    }
    else {
      return target->value;
    }
  }
  */

  virtual void remove(const K & key) { root = helper(root, key); }
  Node * helper(Node * curr, const K & key) {
    if (curr == NULL) {
      return curr;
    }
    if (curr->key == key) {
      if (curr->left == NULL) {
        Node * temp = curr->right;
        delete curr;
        return temp;
      }
      else if (curr->right == NULL) {
        Node * temp = curr->left;
        delete curr;
        return temp;
      }
      else {
        //get min key
        curr = curr->right;
        if (curr == NULL) {
          std::cerr << "Cannot find the min key" << std::endl;
          exit(EXIT_FAILURE);
        }
        Node * travesal = curr;
        K temp = curr->key;
        while (travesal != NULL) {
          temp = travesal->key;
          travesal = travesal->left;
        }
        K k = temp;
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
};
