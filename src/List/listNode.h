#ifndef LISTNODE_H_
#define LISTNODE_H_

template <typename T>
class ListNode;  // 声明，方便下文使用模板别名

template <typename T>
using ListNodePtr = ListNode<T> *;  // 模板别名

template <typename T>
class ListNode {  // 以双向链表实现
 public:
  T data;               // 数值
  ListNodePtr<T> pred;  //前驱
  ListNodePtr<T> succ;  // 后继

  ListNode() {}  // 针对 header 和 trailer 的构造
  ListNode(const T &e, ListNodePtr<T> p = nullptr, ListNodePtr<T> s = nullptr)
      : data(e), pred(p), succ(s) {}

  ListNodePtr<T> insertAsPred(const T &e);  // 前插入
  ListNodePtr<T> insertAsSucc(const T &e);  // 后插入
};

#endif  // LISTNODE_H_