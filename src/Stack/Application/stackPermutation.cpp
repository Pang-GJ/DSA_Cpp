// 栈混洗
#include <iostream>

#include "../../Vector/Vector.h"
#include "../StackList.h"

// 不保证一定对。。。
bool stackPermutation(Vector<int> &src, Vector<int> &des) {
  Stack<int> S;
  Stack<int> A, B;
  for (int i = 0; i < src.size(); ++i) A.push(src[i]);

  int i = 0;
  while (!src.empty()) {
    S.push(A.pop());
    if (S.top() == des[i]) {
      B.push(S.pop());
      i++;
    }
  }

  while (i < des.size()) {
    if (S.top() == des[i]) {
      B.push(S.pop());
      i++;
    } else {
      return false;
    }
  }

  if (S.empty())
    return true;
  else
    return false;
}