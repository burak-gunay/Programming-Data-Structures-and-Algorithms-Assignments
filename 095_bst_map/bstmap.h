#include <algorithm>
#include <stdexcept>

#include "map.h"
#ifndef __BSTMAP_H__
#define __BSTMAP_H__
template<typename K, typename V>
class BstMap : public Map<K, V>
{
 private:
  class Node
  {
   public:
    K key;
    V value;
    Node * left;
    Node * right;
    Node() : left(NULL), right(NULL) {}  // Added this to check
    Node(K k_key, V v_value) : key(k_key), value(v_value), left(NULL), right(NULL) {}
    ~Node() {}
  };

 public:
  Node * root;
  BstMap() : root(NULL) {}
  void copy(Node * curr) {
    if (curr != NULL) {  //inorder traversal
      add(curr->key, curr->value);
      copy(curr->left);
      copy(curr->right);
    }
  }
  BstMap(const BstMap & rhs) : root(NULL) { copy(rhs.root); }
  BstMap & operator=(const BstMap & rhs) {
    BstMap temp(rhs);
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
  virtual ~BstMap() { destroy(root); }
  virtual void add(const K & key, const V & value) {
    Node ** curr = &root;
    while (*curr != NULL) {
      if (key < (*curr)->key) {
        curr = &(*curr)->left;
      }
      else if (key > (*curr)->key) {
        curr = &(*curr)->right;
      }
      else {
        (*curr)->value = value;
        return;  // so the func ends
      }
    }
    *curr = new Node(key, value);
  }
  virtual const V & lookup(const K & key) const throw(std::invalid_argument) {
    Node * curr = root;
    while (curr != NULL) {
      if (key == curr->key) {
        return curr->value;
      }
      else if (key < curr->key) {
        curr = curr->left;
      }
      else {
        curr = curr->right;
      }
    }
    throw std::invalid_argument("No corresponding key\n");
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
          (*curr)->value = (*p)->value;
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

  friend void testBST(void);
};
#endif
