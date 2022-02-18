#include "BinNode.h"

#include <cstdlib>

template <typename T>
void BinNode<T>::insertAtLeft(const T &e) {
  if (!_lChild) _lChild = new BinNode<T>(e, this);
}

template <typename T>
void BinNode<T>::insertAtRight(const T &e) {
  if (!_rChild) _rChild = new BinNode<T>(e, this);
}

template <typename T>
int BinNode<T>::size() {
  int sz = 1;
  if (_lChild != nullptr) sz += _lChild->size();
  if (_rChild != nullptr) sz += _rChild->size();
  return sz;
}

template <typename T>
template <typename VST>
void BinNode<T>::travPre(VST &visit) {
  switch (rand() % 3) {
    case 1:
      travPre_I1(this, visit);
      break;
    case 2:
      travPre_I2(this, visit);
      break;
    default:
      travPre_R(this, visit);
      break;
  }
}

