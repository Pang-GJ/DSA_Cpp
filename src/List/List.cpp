#include "List.h"

#include "listNode.h"

template <typename T>
void List<T>::init() {
  header = new ListNodePtr<T>;
  trailer = new ListNodePtr<T>;

  header->pred = nullptr;
  header->succ = trailer;

  trailer->succ = nullptr;
  trailer->pred = header;

  _size = 0;
}

template <typename T>
T List<T>::operator[](Rank r) const {
  ListNodePtr<T> p = first();
  while (r--) p = p->succ;
  return p->data;
}

template <typename T>
ListNodePtr<T> List<T>::insert(const T &e, ListNodePtr<T> p) {
  _size++;
  return p->insertAsPred(e);
}

template <typename T>
ListNodePtr<T> List<T>::insert(ListNodePtr<T> p, const T &e) {
  _size++;
  return p->insertAsSucc(e);
}

template <typename T>
T List<T>::remove(ListNodePtr<T> p) {
  T e = p->data;
  p->pred->succ = p->succ;
  p->succ->pred = p->pred;
  delete p;
  _size--;
  return e;
}

template <typename T>
int List<T>::clear() {
  int oldSize = _size;
  while (0 < _size) remove(header->succ);

  return oldSize;
}

template <typename T>
List<T>::~List() {
  clear();
  delete header;
  delete trailer;
}

template <typename T>
void List<T>::copyNodes(ListNodePtr<T> p, int n) {
  init();
  ListNodePtr<T> temp = header;
  while (n--) {
    insertAsLast(p->data);
    p = p->succ;
  }
}

template <typename T>
List<T>::List(const List<T> &L) {
  copyNodes(L.first(), L.size());
}

template <typename T>
List<T>::List() {
  init();
}