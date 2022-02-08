#include "BinNode.h"

template<typename T>
void BinNode<T>::insertAtLeft(const T &e) {
  if (!_lChild)
    _lChild = new BinNode<T>(e, this);
}

template<typename T>
void BinNode<T>::insertAtRight(const T &e) {
  if (!_rChild)
    _rChild = new BinNode<T>(e, this);
}