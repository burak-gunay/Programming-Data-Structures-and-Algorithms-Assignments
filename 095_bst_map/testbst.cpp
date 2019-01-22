#include <iostream>

#include "assert.h"
#include "bstmap.h"
void testBST(void) {
  BstMap<int, int> * test1 = new BstMap<int, int>();
  assert(test1->root == NULL);  // test initialized properly
  (*test1).add(10, 20);
  assert(test1->root != NULL);                                      //check adds properly
  assert(test1->root->key == 10);                                   //check key updated
  assert(test1->root->value == 20);                                 //check value updated
  assert(test1->root->left == NULL && test1->root->right == NULL);  // check if leaf node
  (*test1).add(5, 20);

  assert(test1->root->left != NULL &&
         test1->root->right == NULL);  // check if second element added correctly
  assert(test1->root->left->key == 5 &&
         test1->root->left->value == 20);  // check values of second element are correct

  (*test1).add(5, 30);  // adding another node with same key, should change value
  assert(test1->root->left->value == 30 &&
         test1->root->left->key == 5);  // check if updated properly
  (*test1).add(15, 2);
  (*test1).add(13, 2);  //5 r(10)  13 15
  (*test1).add(16, 2);  // 5 r(10) 13 15 16
  (*test1).add(3, 5);   // 3 5 r(10) 13 15 16
  (*test1).remove(5);
  std::cout << "Value of roots left value is" << test1->root->left->key << std::endl;
  assert(test1->root->left->key == 3);
  (*test1).remove(15);  // should be 3 r(10) 13 16 // problem with removing double
  std::cout << "Right child of root is" << test1->root->right->key << std::endl;
  BstMap<int, int> * test2 = new BstMap<int, int>();
  test2 = test1;
  assert(test2->root->key == 10);
  assert(test2->root->left->key == 3);
  delete test1;
  delete test2;  // problem with deleting this? problem arises here

  //delete test1;  //can delete multiple elements no problem with here

  // const int & test1value_1 = (*test1).lookup(15);
  // assert(test1value_1 == 2);  // Check if receive correct value

  // const int & test1value_2 = (*test1).lookup(5);
  // assert(test1value_2 == 30);  // Check if receive correct value

  // try {  // check for exception
  //   const int & test1value_3 = (*test1).lookup(100);
  //   assert(test1value_3 != 20);  //check if fails incorrect case
  // }
  // catch (std::invalid_argument) {
  //   std::cout << "Exception caught\n" << std::endl;
  // }
  // BstMap<int, int> * test2 = new BstMap<int, int>();
  // (*test2).add(11, 18);
  // assert(test2->root != NULL);
  // (*test2).remove(11);
  // assert(test2->root == NULL);  //did it delete one node?
  // (*test2).add(10, 20);
  // (*test2).add(5, 10);  //now root only has left children
  // (*test2).remove(10);  //removes the element root is pointing at, now root should point at 5
  // assert(test2->root->key == 5);

  // LinkedList & operator=(const LinkedList & rhs) {
  // LinkedList tempList;
  // tempList.head = head;
  // tempList.size = size;

  // head = NULL;
  // tail = NULL;
  // size = 0;
  // Node * temp = rhs.head;  //rhs null check deleted here
  // for (int i = 0; i < rhs.size; i++) {
  //   addBack(temp->data);
  //   temp = temp->next;
  // }
  // return *this;
}

int main(void) {
  testBST();

  std::cout << "All tests ended successfuly" << std::endl;
  return 0;
}
