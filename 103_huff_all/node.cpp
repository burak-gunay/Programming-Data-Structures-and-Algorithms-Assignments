#include "node.h"

#include <map>
void Node::buildMap(BitString b, std::map<unsigned, BitString> & theMap) {
  if (sym != NO_SYM) {  //contains a symbol, leaf node
    assert((left == NULL) && (right == NULL));
    std::pair<unsigned, BitString> pair(sym, b);
    theMap.insert(pair);
  }
  else {                                        //doesnt contain symbol, internal node
    assert((left != NULL) && (right != NULL));  //check both not NULL
    BitString c;
    c = b.plusZero();
    left->buildMap(c, theMap);
    BitString d;
    d = b.plusOne();
    right->buildMap(d, theMap);
  }
}
