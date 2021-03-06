#include <assert.h>
1;
95;
0c
#include <cstdlib>
#include <iostream>

#include "ll.h"
    void
    testList(void) {
  LinkedList<int> list_1;       //Test case for default constructor
  assert(list_1.head == NULL);  //Checking whether constructed correctly
  assert(list_1.tail == NULL);
  assert(list_1.size == 0);
  assert(list_1.remove(0) == false);  //Check if incorrect remove returns false
  LinkedList<int> list_1_1;
  list_1_1 = list_1;  //Check assignment operator with empty list
  assert(list_1_1.head == NULL);
  assert(list_1_1.tail == NULL);
  assert(list_1_1.size == 0);
  assert(list_1_1.remove(500) == false);
  assert(list_1_1.getSize() == 0);
  list_1_1.addFront(3);  // 3
  assert(list_1_1.head->data == 3);
  list_1_1.addFront(5);              // 5 3
  assert(list_1_1.head->data == 5);  //check if values implemented properly
  assert(list_1_1.tail->data == 3);
  assert(list_1_1.head->next->prev->data == 5);  //Check if connected properly

  list_1.addFront(4);               // 4
  assert(list_1.head->data == 4);   //Check for addFront
  list_1.addBack(10);               // 4 10
  assert(list_1.tail->data == 10);  //Check for addBack
  assert(list_1.head->next->data == 10);
  assert(list_1.head->next->prev->data == 4);  //Checking if prev proper
  assert(list_1.size == 2);                    //Check for size
  assert(list_1.head->prev == NULL);
  assert(list_1.tail->next == NULL);
  list_1.addFront(-5);
  assert(list_1.head->data == -5);  //check if can handle neg values
  list_1.addFront(0);
  assert(list_1.head->data == 0);  //check if can handle zero values
  assert(list_1.size == 4);        //LL is now 4 elements, 0 -5 4 10
  assert(list_1[0] == 0 && list_1[1] == -5 && list_1[2] == 4 && list_1[3] == 10);  //check [] op
  try {
    list_1[100];
  }
  catch (std::exception e) {  //checked faulty behavior
    std::cout << "Exception handled\n";
  }
  assert(list_1.getSize() == 4);   //Check getsize
  int list_1var = list_1.find(4);  //Gives index when input given
  assert(list_1var == 2);

  LinkedList<int> list_2;  // Test case for assignment operator
  list_2 = list_1;
  assert(list_1.size == list_2.size);  //Test  case 10, unequal size when assignment operator
  assert(list_1.head->data == list_2.head->data);
  assert(list_2.tail->next == NULL);
  assert(list_2.head->prev == NULL);
  assert(list_2.remove(100) == false);  //incorrect remove, check if returns false
  assert(list_2[0] == 0 && list_2[1] == -5 && list_2[2] == 4 && list_2[3] == 10);  //check [] op
  assert(list_2.getSize() == 4);                                                   //Check getsize
  assert(list_2.remove(4) == true);  //check if correct remove is done 0 -5 10
  assert(list_2.size == 3 && list_2.getSize() == 3 && list_2[2] == 10);  //check if size updated
  //Test 1&2

  LinkedList<int> list_3;  //Single element, checking whether tail and head point to same Node
  list_3.addBack(5);
  assert(list_3.head == list_3.tail);
  assert(list_3.head->data == list_3.tail->data);
  list_3.remove(3);  //false remove, should not delete
  assert(list_3.head->data == 5);
  list_3.remove(5);  //correct remove, should remove now
  assert(list_3.size == 0);

  LinkedList<int> list_4_1;
  LinkedList<int> list_4 = list_4_1;
  list_4.addBack(5);               //list_4 = 5
  assert(list_4.head->data == 5);  //check if when add to back, head still points
  //assert(list_4_1.size == 0 && list_4_1.getSize() == 0);  //check if original size altered
  //assert(list_4.tail->prev == NULL && list_4.head->next == NULL);
  //const int zero = 0;
  //const int list_4_val = list_4[zero];
  //assert(list_4_val == 5);  //Check const [] operator

  LinkedList<int> list_5;  //check if destructing nodes properly
  list_5.addFront(10);     //10
  list_5.addFront(5);      //5 10
  list_5.remove(10);
  assert(list_5.head->prev == NULL && list_5.tail->next == NULL);  //check if remove correct
  assert(list_5.head->data == 5);
  assert(list_5.tail->data == 5);  //check if tail updated as well
  list_5.addFront(8);              // 8 5
  list_5.addFront(10);             //10 8 5
  list_5.remove(8);
  assert(list_5.head->data == 10);
  assert(list_5.tail->data == 5);
  list_5.remove(10);
  assert(list_5.head->data == list_5.tail->data);

  LinkedList<int> list_6;       //now checking doublylinked pointers
  list_6.addBack(3);            // 3
  list_6.addBack(4);            // 3 4
  list_6.addBack(5);            // 3 4 5
  assert(list_6.find(5) == 2);  //Checking with addBack, if it adds properly
  list_6.remove(4);             //Now, should be 3 5
  assert(list_6.head->next->data == 5 &&
         list_6.tail->prev->data == 3);  //First, check if connected proper
}

int main(void) {
  testList();
  return EXIT_SUCCESS;
}
