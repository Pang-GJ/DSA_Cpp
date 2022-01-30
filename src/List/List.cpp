#include "List.h"

#include "listNode.h"

template <typename T>
void List<T>::init() {
  header = new ListNodePtr<T>;
  tailer = new ListNodePtr<T>;

  header->pred = nullptr;
  header->succ = tailer;

  tailer->succ = nullptr;
  tailer->pred = header;

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
  delete tailer;
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
  return find(e, _size, tailer);
}

template <typename T>
ListNodePtr<T> List<T>::search(const T &e, int n, ListNodePtr<T> p) {
  while (0 <= n--) {
    p = p->pred;
    if (p->data == e) break;
  }
  return p;
}

template <typename T>
int List<T>::deduplicate() {
  int oldSize = _size;
  ListNodePtr<T> p = first();
  for (Rank r = 0; p != tailer; p = p->succ) {
    ListNodePtr<T> q = find(p->data, r, p);
    if (!q)
      remove(q);
    else
      ++r;  // 无重前缀长度
  }
  return oldSize - _size;  // 删除元素总数
}

template <typename T>
int List<T>::uniquify() {
  int oldSize = _size;
  ListNodePtr<T> p = first(), q = nullptr;
  while (tailer != q) {
    if (p->data != q->data)
      p = q;
    else
      remove(q);
    q = p->succ;
  }
  return oldSize - _size;
}

template <typename T>
void List<T>::selectionSort(ListNodePtr<T> p, int n) {
  ListNodePtr<T> head = p->pred, tail = p;
  for (int i = 0; i < n; ++i) tail = tail->succ;
  while (n--) {
    ListNodePtr<T> max = selectMax(head->succ, n);
    // 为了避免频繁的动态内存分配跟回收
    // new 跟 delete 花费的时间大概是普通操作的100倍
    // 所以这里只交换两个节点的数据域
    swap(tail->pred->data, max->data);
    tail = tail->pred;
    n--;
  }
}

template <typename T>
ListNodePtr<T> List<T>::selectMax(ListNodePtr<T> p, int n) {
  ListNodePtr<T> max = p;
  while (n--) {
    if (p->data >= max->data) max = p;
    p = p->succ;
  }
  return max;
}

template <typename T>
void List<T>::insertionSort(ListNodePtr<T> p, int n) {
  for (int r = 0; r < n; ++r) {
    ListNodePtr<T> target = search(p->data, r, p);
    insert(target, p->data);
    p = p->succ;
    remove(p->pred);
  }
}