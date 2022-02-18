#include "../Stack/StackList.h"
#include "BinNode.h"

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