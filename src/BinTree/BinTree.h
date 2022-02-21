#ifndef BINTREE_H_
#define BINTREE_H_

#include "BinNode.h"

template<typename T>
class BinTree {
 protected:
  int _size; // 规模
  BinNodePtr<T> _root; // 根节点
  virtual int updateHeight(BinNodePtr<T> x); // 更新节点 x 的高度
  void updateHeightAbove(BinNodePtr<T> x);   // 更新节点 x 及其祖先的高度

 public:
  BinTree() : _size(0), _root(nullptr) {}
  ~BinTree();
  
  int size() const {return _size;}
  bool empty() const {return !_root;}
  BinNodePtr<T> root() const { return _root; }
  BinNodePtr<T> insertAsRoot(const T& e);
  BinNodePtr<T> insertAsLC(BinNodePtr<T> x, const T& e);
  BinNodePtr<T> insertAsRC(BinNodePtr<T> x, const T& e);
  BinNodePtr<T> attachAsLC(BinNodePtr<T> x, BinTree<T>* &t);
  BinNodePtr<T> attachAsRC(BinNodePtr<T> x, BinTree<T>* &t);

  int remove(BinNodePtr<T> x);  // 删除以位置 x 处节点为根的子树，返回该子树原先的规模

  // 遍历
  template<typename VST>
  void travLevel(VST &visit) { if (_root) _root->travLevel(visit); }

  template<typename VST>
  void travPre(VST &visit) { if (_root) _root->travPre(visit); }

  template<typename VST>
  void travIn(VST &visit) { if (_root) _root->travIn(visit); }

  template<typename VST>
  void travPost(VST &visit) { if (_root) _root->travPost(visit); }
  
};
#endif // BINTREE_H_