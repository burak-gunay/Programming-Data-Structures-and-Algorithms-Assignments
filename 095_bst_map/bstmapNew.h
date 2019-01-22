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
  Node * removehelper(const K & key, Node * curr) {
    if (curr == NULL) {
      return curr;
    }
    if (key < curr->key) {
      curr->left = removehelper(key, curr->left);  //recursively call left subtree, update
    }
    else if (key > curr->key) {
      curr->right = removehelper(key, curr->right);  //recursively call right subtree, update
    }
    else {                       // key to be removed is caught
      if (curr->left == NULL) {  //either only left child null, or both child null
        Node * temp = curr->right;
        delete curr;
        return temp;
      }
      else if (curr->right == NULL) {
        Node * temp = curr->left;
        delete curr;
        return temp;
      }
      else {  // both children are not NULL
        Node * minNode = curr->right;
        while (minNode->left != NULL) {
          minNode = minNode->left;  //update minNode until left is null
        }
        curr->key = minNode->key;  //update key&value of curr
        curr->value = minNode->value;
        curr->right = removehelper(
            minNode->key,
            minNode);  // second parameter could be minNode as well, either case should work
        return curr;
      }
    }
    return curr;  //returning modified root
  }
  virtual void remove(const K & key) {
    if (this->root == NULL) {
      return;
    }
    else {
      root = removehelper(key, root);
    }
  }

  friend void testBST(void);
};
#endif
