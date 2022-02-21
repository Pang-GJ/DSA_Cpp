#include "BinTree.h"
#include "BinNode.h"

template<typename T>
BinTree<T>::~BinTree() {
  if (0 < _size)
    remove(_root);
}

template<typename T>
BinNodePtr<T> BinTree<T>::insertAsRoot(const T &e) {
  _size = 1;
  _root = new BinNode<T>(e);
  return _root;
}

template<typename T>
BinNodePtr<T> BinTree<T>::insertAsLC(BinNodePtr<T> x, const T &e) {
  ++_size;
  x->insertAtLeft(e);
  updateHeightAbove(x);
  return x->_lChild;
}

template<typename T>
BinNodePtr<T> BinTree<T>::insertAsRC(BinNodePtr<T> x, const T &e) {
  ++_size;
  x->insertAtRight(e);
  updateHeightAbove(x);
  return x->_rChild;
}