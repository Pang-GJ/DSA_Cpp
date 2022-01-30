#include "listNode.h"

template<typename T>
ListNodePtr<T> ListNode<T>::insertAsPred(const T &e) {
  ListNodePtr<T> x = new ListNode<T>(e, pred, this);
  pred->succ = x;
  pred = x;
  return x;
}

template <typename T>
ListNodePtr<T> ListNode<T>::insertAsSucc(const T &e) {
  ListNodePtr<T> x = new ListNode<T>(e, this, succ);
  succ->pred = x;
  succ = x;
  return x;
}