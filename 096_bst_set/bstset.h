#include <algorithm>
#include <stdexcept>

#include "set.h"
#ifndef __BSTSET_H__
#define __BSTSET_H__
template<typename K>
class BstSet : public Set<K>
{
 private:
  class Node
  {
   public:
    K key;
    Node * left;
    Node * right;
    Node() : left(NULL), right(NULL) {}  // Added this to check
    Node(K k_key) : key(k_key), left(NULL), right(NULL) {}
    ~Node() {}
  };

 public:
  Node * root;
  BstSet() : root(NULL) {}
  void copy(Node * curr) {
    if (curr != NULL) {  //inorder traversal
      add(curr->key);
      copy(curr->left);
      copy(curr->right);
    }
  }
  BstSet(const BstSet & rhs) : root(NULL) { copy(rhs.root); }
  BstSet & operator=(const BstSet & rhs) {
    BstSet temp(rhs);
    std::swap(root, temp.root);
    return *this;

  }  //faulty bit
  void destroy(Node * curr) {
    if (curr != NULL) {
      destroy(curr->left);
      destroy(curr->right);
      delete curr;
    }
  }
  virtual ~BstSet() { destroy(root); }
  virtual void add(const K & key) {
    Node ** curr = &root;
    while (*curr != NULL) {
      if (key < (*curr)->key) {
        curr = &(*curr)->left;
      }
      else if (key > (*curr)->key) {
        curr = &(*curr)->right;
      }
      else {
        return;  // so the func ends
      }
    }
    *curr = new Node(key);
  }
  virtual bool contains(const K & key) const {
    Node * curr = root;
    while (curr != NULL) {
      if (key == curr->key) {
        return true;
      }
      else if (key < curr->key) {
        curr = curr->left;
      }
      else {
        curr = curr->right;
      }
    }
    return false;
  }
  virtual void remove(const K & key) {
    Node ** curr = &root;
    while (*curr != NULL) {
      if (((*curr)->key) == key) {
        if ((*curr)->left != NULL && (*curr)->right != NULL) {
          Node ** p = &((*curr)->left);
          while (((*p)->right) != NULL) {
            p = &((*p)->right);
          }
          (*curr)->key = (*p)->key;
          Node * toFree = *p;
          *p = (*p)->left;
          delete toFree;
        }
        else {
          if ((*curr)->left == NULL) {
            Node * temp = *curr;
            (*curr) = (*curr)->right;
            delete temp;
          }
          else if ((*curr)->right == NULL) {
            Node * temp = *curr;
            (*curr) = (*curr)->left;
            delete temp;
          }
          else {
            delete (*curr);
            *curr = NULL;
          }
        }
      }
      else if (key < (*curr)->key) {
        curr = &((*curr)->left);
      }
      else {
        curr = &((*curr)->right);
      }
    }
  }
};
#endif
