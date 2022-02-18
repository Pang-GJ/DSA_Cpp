#include "BinNode.h"
#include "../Stack/StackList.h"

// 先序遍历递归版
template<typename T ,typename VST>
void travPre_R(BinNodePtr<T> x, VST &visit) {
  if (x == nullptr) return;
  visit(x->_data);
  travPre_R(x->_lChild, visit);
  travPre_R(x->_rChild, visit);
}

// 先序遍历迭代版#1
template<typename T, typename VST>
void travPre_I1(BinNodePtr<T> x, VST &visit) {
  Stack<BinNodePtr<T>> stk; // 辅助栈
  stk.push(x);  // 根节点入栈
  while (!stk.empty()) {
    // 弹出并访问当前节点，并令其孩子入栈(先右后左)
    BinNodePtr<T> node = stk.top();
    stk.pop();
    visit(x->_data);
    if (x->_rChild != nullptr)
      stk.push(x->_rChild);
    if (x->_lChild != nullptr)
      stk.push(x->_lChild);
  }
}

// 先序遍历迭代版#2
template<typename T, typename VST>
// 从当前节点出发，沿左分支不断深入，直至没有左分支
// 路途中遇到的节点立即访问
static void visitAlongVine(BinNodePtr<T> x, VST &visit, Stack<BinNodePtr<T>> &stk) {
  while (x != nullptr) {
    visit(x->_data);  // 访问当前节点
    if (x->_rChild != nullptr)
      stk.push(x->_rChild);
    x = x->_lChild;
  }
}

template<typename T, typename VST>
void travPre_I2(BinNodePtr<T> x, VST &visit) {
  Stack<BinNodePtr<T>> stk; // 辅助栈
  while (true) {
    visitAlongVine(x, visit, stk);
    if (stk.empty()) break;
    x = stk.top();
    stk.pop();
  }
}