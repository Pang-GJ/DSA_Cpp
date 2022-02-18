#ifndef BINNODE_H_
#define BINNODE_H_

template <typename T>
struct BinNode;
template <typename T>
using BinNodePtr = BinNode<T> *;

template <typename T>
struct BinNode {
  // parent ,leftChild, rightChild, height, data
  BinNode<T> *_parent;
  BinNode<T> *_lChild;
  BinNode<T> *_rChild;

  T _data;
  int _height;

  BinNode(int data = 0, BinNode<T> *parent = nullptr)
      : _data(data),
        _height(0),
        _parent(parent),
        _lChild(nullptr),
        _rChild(nullptr) {}

  // 作为左节点插入
  void insertAtLeft(const T &e);

  // 作为右节点插入
  void insertAtRight(const T &e);

  BinNodePtr<T> succ();  // 取出当前节点的直接后继
  int size();            // 统计当前节点的后代总数

  // 遍历
  template <typename VST>
  void travLevel(VST &);  // 层次遍历

  template <typename VST>
  void travPre(VST &);  // 先序遍历

  template <typename VST>
  void travIn(VST &);  // 中序遍历

  template <typename VST>
  void travPost(VST &);  // 后序遍历
};

#endif  // BINNODE_H_