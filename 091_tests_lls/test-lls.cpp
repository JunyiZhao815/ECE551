#include <assert.h>

#include <cstdlib>
#include <iostream>

#include "il.hpp"

class Tester {
 public:
  // testing for default constructor is done for you
  void testDefCtor() {
    IntList il;
    assert(il.head == NULL);
    assert(il.tail == NULL);
    assert(il.getSize() == 0);
  }
  // example of another method you might want to write
  void testAddFront() {
    // WRITE ME
    IntList il;
    il.addFront(10);
    assert(il.tail->next == NULL);
    assert(il.head->prev == NULL);
    assert(il.head != NULL);
    assert(il.tail != NULL);
    assert(il.head == il.tail);
    assert(il.getSize() == 1);
    assert(il.head->data == 10);

    il.addFront(20);
    assert(il.head != NULL);
    assert(il.tail != NULL);
    assert(il.tail->next == NULL);
    assert(il.head->prev == NULL);
    assert(il.tail == il.head->next);
    assert(il.head == il.tail->prev);
    assert(il.getSize() == 2);
    assert(il.head->data == 20);
    assert(il.tail->data == 10);
    il.remove(10);
    il.remove(20);
  }

  void testAddBack() {
    IntList il;
    // When there is only one node
    il.addBack(1);
    assert(il.head != NULL);
    assert(il.head == il.tail);
    assert(il.getSize() == 1);
    assert(il[0] == 1);
    assert(il.head->data == 1);
    assert(il.head->next == il.head->prev);
    assert(il.head->next == NULL);

    // Two nodes
    il.addBack(2);
    assert(il.head != NULL);
    assert(il.tail != NULL);
    assert(il.getSize() == 2);
    assert(il[0] == 1);
    assert(il[1] == 2);
    assert(il.head->data == 1);
    assert(il.tail->data == 2);
    assert(il.head->prev == NULL);
    assert(il.tail->next == NULL);
    assert(il.head->next->data == 2);
    assert(il.tail->prev == il.head);
    assert(il.head->next == il.tail);

    // Three nodes
    il.addBack(3);
    assert(il.head != NULL);
    assert(il.tail != NULL);
    assert(il.head->prev == NULL);
    assert(il.tail->next == NULL);
  }

  void testRemove() {
    IntList il;
    il.addFront(1);
    il.addFront(2);
    // remove element from tail when 2 elements
    bool flag = il.remove(2);
    assert(flag == true);
    assert(il.tail->next == NULL);
    assert(il.head->prev == NULL);
    assert(il.head != NULL);
    assert(il.tail != NULL);
    assert(il.head == il.tail);
    assert(il.head->next == NULL);
    assert(il.tail->prev == NULL);
    assert(il.getSize() == 1);
    assert(il.head->data == 1);

    // remove element from tail when three elements
    il.addFront(2);
    il.addFront(3);

    bool flag2 = il.remove(1);
    assert(flag2 == true);
    assert(il.tail->next == NULL);
    assert(il.head->prev == NULL);
    assert(il.head != NULL);
    assert(il.tail != NULL);
    assert(il.head->next == il.tail);
    assert(il.tail->prev == il.head);
    assert(il.getSize() == 2);
    assert(il.head->data == 3);
    assert(il.tail->data == 2);

    // remove element from head when three elements
    il.addBack(1);
    bool flag3 = il.remove(3);
    assert(flag3 == true);
    assert(il.tail->next == NULL);
    assert(il.head->prev == NULL);
    assert(il.head != NULL);
    assert(il.tail != NULL);
    assert(il.head->next == il.tail);
    assert(il.tail->prev == il.head);
    assert(il.getSize() == 2);
    assert(il.head->data == 2);
    assert(il.tail->data == 1);
    // remove element from middle when three elements
    il.addFront(3);
    bool flag4 = il.remove(2);
    assert(flag4 == true);
    assert(il.tail->next == NULL);
    assert(il.head->prev == NULL);
    assert(il.head != NULL);
    assert(il.tail != NULL);
    assert(il.head->next == il.tail);
    assert(il.tail->prev == il.head);
    assert(il.getSize() == 2);
    assert(il.head->data == 3);
    assert(il.tail->data == 1);
    // remove element when there is only one element
    bool flag5 = il.remove(1);
    assert(flag5 == true);
    assert(il.tail->next == NULL);
    assert(il.head->prev == NULL);
    assert(il.head != NULL);
    assert(il.tail != NULL);
    assert(il.tail->prev == NULL);
    assert(il.head->next == NULL);
    assert(il.head == il.tail);
    assert(il.getSize() == 1);
    assert(il.head->data == 3);
    // remove element if there are multiply element that is the same
    bool flag6 = il.remove(3);
    assert(flag6 == true);
    assert(il.head == NULL);
    assert(il.tail == NULL);
    assert(il.head == il.tail);
    assert(il.getSize() == 0);

    il.addBack(1);
    il.addBack(2);
    il.addBack(1);
    bool flag7 = il.remove(1);
    assert(flag7 == true);
    assert(il.tail->next == NULL);
    assert(il.head->prev == NULL);
    assert(il.head != NULL);
    assert(il.tail != NULL);
    assert(il.head->next == il.tail);
    assert(il.tail->prev == il.head);
    assert(il.getSize() == 2);
    assert(il.head->data == 2);
    assert(il.tail->data == 1);
    il.remove(2);
    il.remove(1);
    assert(il.remove(5) == false);
  }
  void testThree() {
    IntList * l1 = new IntList();
    l1->addFront(1);
    //check copying
    IntList * l2 = new IntList(*l1);
    assert(l1->head != l2->head);
    assert(l1->tail != l2->tail);
    //checking deleting
    delete l2;
    delete l1;
    IntList * l3 = new IntList();
    IntList * l4 = new IntList();
    l3->addBack(1);
    l3->addBack(2);
    l4->addBack(1);
    l4->addBack(2);
    l4->addBack(3);

    //check assignment
    *l4 = *l3;
    assert(l4->getSize() == 2);
    assert(l3->head->data == l4->head->data);
    assert(l3->tail->data == l4->tail->data);
    assert(l3->head->next->data == l4->tail->data);
    assert(l3->tail->prev->data == l4->head->data);
    assert(l3->head != l4->head);
    assert(l3->tail != l4->tail);
    assert(l4->tail->next == NULL);
    assert(l4->head->prev == NULL);
    delete l3;
    delete l4;
  }
};

int main(void) {
  Tester t;
  t.testDefCtor();
  t.testAddFront();
  t.testAddBack();
  t.testThree();
  t.testRemove();
  // write calls to your other test methods here
  return EXIT_SUCCESS;
}
