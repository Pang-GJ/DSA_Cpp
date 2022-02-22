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

#include <cstddef>
#include <cstdlib>

#include "../Queue/QueueList.h"

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

#include "../Stack/StackList.h"

// 先序遍历递归版
template <typename T, typename VST>
void travPre_R(BinNodePtr<T> x, VST &visit) {
  if (x == nullptr) return;
  visit(x->_data);
  travPre_R(x->_lChild, visit);
  travPre_R(x->_rChild, visit);
}

// 先序遍历迭代版#1
template <typename T, typename VST>
void travPre_I1(BinNodePtr<T> x, VST &visit) {
  Stack<BinNodePtr<T>> stk;  // 辅助栈
  stk.push(x);               // 根节点入栈
  while (!stk.empty()) {
    // 弹出并访问当前节点，并令其孩子入栈(先右后左)
    BinNodePtr<T> node = stk.top();
    stk.pop();
    visit(x->_data);
    if (x->_rChild != nullptr) stk.push(x->_rChild);
    if (x->_lChild != nullptr) stk.push(x->_lChild);
  }
}

// 先序遍历迭代版#2
template <typename T, typename VST>
// 从当前节点出发，沿左分支不断深入，直至没有左分支
// 路途中遇到的节点立即访问
static void visitAlongVine(BinNodePtr<T> x, VST &visit,
                           Stack<BinNodePtr<T>> &stk) {
  while (x != nullptr) {
    visit(x->_data);  // 访问当前节点
    if (x->_rChild != nullptr) stk.push(x->_rChild);
    x = x->_lChild;
  }
}

template <typename T, typename VST>
void travPre_I2(BinNodePtr<T> x, VST &visit) {
  Stack<BinNodePtr<T>> stk;  // 辅助栈
  while (true) {
    visitAlongVine(x, visit, stk);
    if (stk.empty()) break;
    x = stk.top();
    stk.pop();
  }
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

#include <cstddef>
#include <cstdlib>

#include "../Stack/StackList.h"

// 中序遍历递归版
template <typename T, typename VST>
void travIn_R(BinNodePtr<T> x, VST &visit) {
  if (x == nullptr) return;
  travIn_R(x->_lChild, visit);
  visit(x->_data);
  travIn_R(x->_rChild, visit);
}

// 中序遍历迭代版#1
template <typename T>
// 从当前节点出发，沿左分支不断深入，直至没有左分支的节点
static void goAlongVine(BinNodePtr<T> x, Stack<BinNodePtr<T>> &stk) {
  while (x != nullptr) {
    stk.push(x);
    x = x->_lChild;
  }
}

template <typename T, typename VST>
void travIn_I1(BinNodePtr<T> x, VST &visit) {
  Stack<BinNodePtr<T>> stk;  // 辅助栈
  while (true) {
    goAlongVine(x, stk);     // 从当前节点出发，逐批入栈
    if (stk.empty()) break;  // 所有节点都遍历了，退出循环
    x = stk.pop();
    visit(x->_data);  // 弹出当前节点并且访问它
    x = x->_rChild;   // 转向右子树
  }
}

// 中序遍历迭代版#2
template <typename T, typename VST>
void travIn_I2(BinNodePtr<T> x, VST &visit) {
  Stack<BinNodePtr<T>> stk;  // 辅助栈
  while (true) {
    if (x != nullptr) {
      stk.push(x);     // 根节点入栈
      x = x->_lChild;  // 深入遍历左子树
    } else if (!stk.empty()) {
      x = stk.pop();    // 尚未访问的最低祖先节点出栈
      visit(x->_data);  // 访问该祖先节点
      x = x->_rChild;   // 遍历祖先的右子树
    } else
      break;  // 遍历完成
  }
}

// 下面这个不太理解，因为不清楚回溯这个东西
// 中序遍历迭代版#3（无需辅助栈）
template <typename T, typename VST>
void travIn_I3(BinNodePtr<T> x, VST &visit) {
  bool backtrack = false;  // 前一步是否刚从左子树回溯
  while (true) {
    // 若有左子树而且不是刚刚回溯
    if (!backtrack && x->_lChild != nullptr)
      x = x->_lChild;  // 深入遍历左子树
    else {             // 若无左子树或刚刚开始回溯
      visit(x->_data);
      if (x->_rChild != nullptr) {
        x = x->_rChild;
        backtrack = false;
      } else {
        // 回溯，同时，如果抵达末节点，退出
        if (!(x = x->succ())) break;
        backtrack = true;  // 设置回溯标志
      }
    }
  }
}

// 中序遍历迭代版#4（无需辅助栈或标志位）
template <typename T, typename VST>
void travIn_I4(BinNodePtr<T> x, VST &visit) {
  while (true) {
    if (x->_lChild != nullptr)  // 如果有左子树
      x = x->_lChild;           // 深入遍历左子树
    else {                      // 否则， 也就是没有左子树的时候
      visit(x->_data);          // 访问当前节点
      // 如果没有右子树
      while (x->_rChild == nullptr) {
        // 回溯至直接后继，（在没有后继的末节点，退出）
        if (!(x = x->succ()))
          return;
        else
          visit(x->_data);  // 访问当前的新节点
      }
      x = x->_rChild;  // (直至有右分支处)转向非空的右子树
    }
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

#include "../Stack/StackList.h"

// 后序遍历递归版
template <typename T, typename VST>
void travPost_R(BinNodePtr<T> x, VST &visit) {
  if (x == nullptr) return;
  travPost_R(x->_lChild, visit);
  travPost_R(x->_rChild, visit);
  visit(x->_data);
}

// 后序遍历迭代版
template <typename T>
// 在以 stk 栈顶节点为根节点的子树中，找到最高左侧的可见叶节点
static void gotoLeftmostLeaf(Stack<BinNodePtr<T>> &stk) {
  while (BinNodePtr<T> x = stk.top()) {  // 自顶向下，不断检查栈顶节点
    if (x->_lChild != nullptr) {         // 尽可能向左
      if (x->_rChild != nullptr)
        stk.push(x->_rChild);  // 若有右孩子，右孩子先入栈
      stk.push(x->_lChild);    // 左孩子入栈
    } else                     // 迫不得己（没有左孩子）
      stk.push(x->_rChild);    // 迫不得已转向右
  }
  stk.pop();  // 返回之前弹出栈顶的空节点
  // 空节点哪来的？注意，我们迫不得已转向右的时候没有判断是否有右孩子
}

template <typename T, typename VST>
void travPost_I(BinNodePtr<T> x, VST &visit) {
  Stack<BinNodePtr<T>> stk;
  if (x != nullptr) stk.push(x);
  while (!stk.empty()) {  // x 始终为当前节点
    if (stk.top() != x->_parent)  // 若栈顶不是 x 的父亲，也就是x的右兄弟
      gotoLeftmostLeaf(stk);
    x = stk.pop();  // 弹出栈顶（也就是前一节点的后继），并访问之
    visit(x->_data);
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

#endif  // BINNODE_H_