#ifndef LIST_H_
#define LIST_H_

#include "listNode.h"

using Rank = int;

template <typename T>
class List {
 private:
  int _size;
  ListNodePtr<T> header;
  ListNodePtr<T> trailer;

 protected:
  /*.....内部函数*/
  void init();  // 初始化，构造列表时统一调用

 public:
  /*.....构造函数*/
  List(); // 默认构造
  List(const List<T> &L); // 复制构造
  // 复制另一个列表的节点
  void copyNodes(ListNodePtr<T> p, int n);
  /*.....析构函数*/
  ~List();
  /*.....只读接口*/
  ListNodePtr<T> first() const { return header->succ; }
  ListNodePtr<T> last() const { return trailer->pred; }
  int size() const { return _size; }
  T operator[](Rank r) const;  // 重载下标运算符
  ListNodePtr<T> find(const T &e, int n, ListNodePtr<T> p);
  ListNodePtr<T> find(const T &e);

  /*.....可写接口*/
  // 把 e 当作 p 的前驱节点插入
  ListNodePtr<T> insert(const T &e, ListNodePtr<T> p);
  // 把 e 当作 p 的后继节点插入
  ListNodePtr<T> insert(ListNodePtr<T> p, const T &e);
  // e 当作首节点插入
  ListNodePtr<T> insertAsFirst(const T &e) { insert(e, header->succ); }
  // e 当作末节点插入
  ListNodePtr<T> insertAsLast(const T &e) { insert(trailer->succ, e); }
  // 删除合法节点 p ，返回其数值
  T remove(ListNodePtr<T> p);
  // 清空列表，返回原来列表的大小
  int clear();
  // 去重
  int deduplicate();
  /*.....遍历接口*/
};

#endif