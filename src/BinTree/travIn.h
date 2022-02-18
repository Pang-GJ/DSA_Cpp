#include <cstddef>
#include <cstdlib>

#include "../Stack/StackList.h"
#include "BinNode.h"

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