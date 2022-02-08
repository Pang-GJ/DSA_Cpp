#ifndef BINNODE_H_
#define BINNODE_H_

template <typename T>
struct BinNode {
  // parent ,leftChild, rightChild, height, data
  BinNode<T> *_parent;
  BinNode<T> *_lChild;
  BinNode<T> *_rChild;

  T _data;

  BinNode(int data = 0, BinNode<T> *parent = nullptr)
      : _data(data), _parent(parent), _lChild(nullptr), _rChild(nullptr) {}

  // 作为左节点插入
  void insertAtLeft(const T &e);

  // 作为右节点插入
  void insertAtRight(const T &e);
};

#endif  // BINNODE_H_