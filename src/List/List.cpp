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
  while (n--) {
    insertAsLast(p->data);
    p = p->succ;
  }
}

template <typename T>
List<T>::List(const List<T> &L) {
  init();
  copyNodes(L.first(), L.size());
}

template <typename T>
List<T>::List() {
  init();
}

template <typename T>
ListNodePtr<T> List<T>::find(const T &e, int n, ListNodePtr<T> p) {
  while (n--) {
    p = p->pred;  // 从 p 之前查找, 不包括p
    if (e == p->data) return p;
  }
  return nullptr;  // 查找失败
}

template <typename T>
ListNodePtr<T> List<T>::find(const T &e) {
  return find(e, _size, trailer);
}

template <typename T>
int List<T>::deduplicate() {
  int oldSize = _size;
  ListNodePtr<T> p = first();
  for (Rank r = 0; p != trailer; p = p->succ) {
    ListNodePtr<T> q = find(p->data, r, p);
    if (!q)
      remove(q);
    else
      ++r;  // 无重前缀长度
  }
  return oldSize - _size;   // 删除元素总数
}