#ifndef __LL_HPP__
#define __LL_HPP__

#include <assert.h>

#include <cstdlib>
#include <exception>
#include <iostream>

//YOUR CODE GOES HERE

template<typename T>
class LinkedList {
 private:
  class Node {
   public:
    T data;
    Node * next;
    Node * prev;
    Node(T d) : data(d), next(NULL), prev(NULL){};
  };

 private:
  Node * head;
  Node * tail;
  int size;

 public:
  LinkedList() : head(NULL), tail(NULL), size(0) {}
  ~LinkedList() {
    while (head != NULL) {
      Node * temp = head->next;
      delete head;
      head = temp;
    }
  }
  LinkedList(const LinkedList & rhs) : head(NULL), tail(NULL), size(0) {
    Node * temp = rhs.head;
    while (temp != NULL) {
      addBack(temp->data);
      temp = temp->next;
    }
  }

  LinkedList & operator=(const LinkedList & rhs) {
    if (this != &rhs) {
      LinkedList ll(rhs);
      std::swap(size, ll.size);
      std::swap(head, ll.head);
      std::swap(tail, ll.tail);
    }
    return *this;
  }
  void addFront(const T & item) {
    ++size;
    Node * temp = new Node(item);
    temp->next = head;
    if (tail == NULL) {
      tail = head;
    }
    else {
      head->prev = temp;
      head = temp;
    }
  }
  void addBack(const T & item) {
    size++;
    Node * temp = new Node(item);
    temp->prev = tail;
    if (head == NULL) {
      head = tail;
    }
    else {
      tail->next = temp;
      tail = temp;
    }
  }

  bool remove(const T & item) {
    Node * temp = head;
    while (temp != NULL) {
      if (temp->data == item) {
        --size;
        if (temp->next == NULL && temp->prev == NULL) {
          head = NULL;
          tail = NULL;
          delete temp;
          return true;
        }
        else if (temp->prev == NULL) {
          head = temp->next;
          head->prev = NULL;
          delete temp;
          return true;
        }
        else if (temp->next == NULL) {
          tail = temp->prev;
          tail->next = NULL;
          delete temp;
          return true;
        }
        else {
          temp->prev->next = temp->next;
          temp->next->prev = temp->prev;
          delete temp;
          return true;
        }
      }
      temp = temp->next;
    }
    return false;
  }
  class e : public std::exception {
   public:
    const char * what() const throw() { return "index is out of boundary!"; }
  };
  T & operator[](int index) {
    try {
      if (index >= size || index < 0) {
        throw e();
      }
    }
    catch (e & e) {
      std::cerr << e.what() << std::endl;
    }
    Node * temp = head;
    for (int i = 0; i < size; i++) {
      temp = temp->next;
    }
    return temp->data;
  }
  T & operator[](int index) const {
    try {
      if (index > size || index < 0) {
        throw e();
      }
    }
    catch (e & e) {
      std::cerr << e.what() << std::endl;
    }
    Node * temp = head;

    for (int i = 0; i < size; i++) {
      temp = temp->next;
    }
    return temp->data;
  }
  int find(const T & item) const {
    int index = 0;
    Node * temp = head;
    while (temp != NULL) {
      if (temp->data == item) {
        return index;
      }
      ++index;
      temp = temp->next;
    }
    return -1;
  }

  int getSize() const { return size; }
};

#endif
