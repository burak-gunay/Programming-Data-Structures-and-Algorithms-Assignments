#ifndef _LL_H_
#define _LL_H_
#include <assert.h>

#include <cstdlib>
#include <exception>
template<typename T>
class LinkedList
{
  class Node
  {
   public:
    T data;
    Node * next;
    Node * prev;
    Node() : data(0), next(NULL), prev(NULL) {}
    Node(const T & item, Node * next_t, Node * prev_t) : data(item), next(next_t), prev(prev_t) {}
    ~Node() {}
  };
  Node * head;
  Node * tail;
  int size;
  class outofbounds_exp : public std::exception
  {
   public:
    outofbounds_exp() {}
  };

 public:
  void addFront(const T & item) {
    if (head == NULL) {
      head = new Node(item, NULL, NULL);
      tail = head;
      size++;
    }
    else {
      Node * temp = new Node(item, head, NULL);
      head->prev = temp;
      head = temp;
      size++;
    }
  }
  void addBack(const T & item) {
    if (head == NULL) {
      tail = new Node(item, NULL, NULL);
      head = tail;
      size++;
    }
    else {
      Node * temp = new Node(item, NULL, tail);
      tail->next = temp;
      tail = temp;
      size++;
    }
  };
  bool remove(const T & item) {  //check false rn
    if (head == NULL) {          // if empty list
      return false;
    }
    Node * temp = head;
    for (int i = 0; i < size; i++) {
      if (item == temp->data) {
        if (temp->prev == NULL) {
          head = temp->next;
        }
        if (temp->prev != NULL) {
          temp->prev->next = temp->next;
        }
        if (temp->next == NULL) {
          tail = temp->prev;
        }
        if (temp->next != NULL) {
          temp->next->prev = temp->prev;
        }
        delete temp;
        size--;
        return true;
      }
      temp = temp->next;
    }
    return false;
  }

  T & operator[](int index) {
    Node * temp = head;
    for (int i = 0; i < size; i++) {
      if (i == index) {
        return temp->data;
      }
      temp = temp->next;
    }

    throw outofbounds_exp();
  }
  const T & operator[](int index) const {  // care here
    Node * temp = head;
    for (int i = 0; i < size; i++) {
      if (i == index) {
        return temp->data;
      }
      temp = temp->next;
    }
    throw outofbounds_exp();
  }

  int find(const T & item) const {
    Node * temp = head;
    for (int i = 0; i < size; i++) {
      if (item == temp->data) {
        return i;
      }
      temp = temp->next;
    }
    return -1;
  }
  LinkedList() : head(NULL), tail(NULL), size(0) {}
  LinkedList(const LinkedList & rhs) : head(NULL), tail(NULL), size(0) {
    Node * temp = rhs.head;
    for (int i = 0; i < rhs.size; i++) {
      addBack(temp->data);
      temp = temp->next;
    }
  }

  LinkedList & operator=(const LinkedList & rhs) {
    LinkedList tempList;
    tempList.head = head;
    tempList.size = size;

    head = NULL;
    tail = NULL;
    size = 0;
    Node * temp = rhs.head;  //rhs null check deleted here
    for (int i = 0; i < rhs.size; i++) {
      addBack(temp->data);
      temp = temp->next;
    }
    return *this;
  }
  ~LinkedList() {
    if (size == 0) {
    }
    else {
      for (int i = 0; i < size - 1; i++) {
        head = head->next;
        delete head->prev;
      }
      delete head;
    }
  }
  int getSize() const { return size; }
};

#endif
