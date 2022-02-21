#include "BinNode.h"

#include <cstddef>
#include <cstdlib>

#include "../Queue/QueueList.h"
#include "travIn.h"
#include "travPost.h"
#include "travPre.h"

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

template <typename T>
template <typename VST>
void BinNode<T>::travIn(VST &visit) {
  switch (rand() % 5) {
    case 1:
      travIn_I1(this, visit);
      break;
    case 2:
      travIn_I2(this, visit);
      break;
    case 3:
      travIn_I3(this, visit);
      break;
    case 4:
      travIn_I4(this, visit);
      break;
    default:
      travIn_R(this, visit);
      break;
  }
}

template <typename T>
template <typename VST>
void BinNode<T>::travPost(VST &visit) {
  switch (rand() % 2) {
    case 1:
      travPost_I(this, visit);
      break;
    default:
      travPost_R(this, visit);
      break;
  }
}

template <typename T>
template <typename VST>
void BinNode<T>::travLevel(VST &visit) {
  Queue<BinNodePtr<T>> que;
  que.enqueue(this);
  while (!que.empty()) {
    BinNodePtr<T> node = que.front();
    que.dequeue();
    visit(node->_data);
    if (node->_lChild != nullptr) que.enqueue(node->_lChild);
    if (node->_rChild != nullptr) que.enqueue(node->_rChild);
  }
}