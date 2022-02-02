#include <iostream>

#include "../StackList.h"

bool paren(char expr[], int low, int high) {
  Stack<char> S;
  for (int i = low; i < high; ++i) {
    if (expr[i] == '(')
      S.push(expr[i]);
    else if (expr[i] == ')' && !S.empty())
      S.pop();
    else
      return false;
  }
  return S.empty();
}

// 拓展到多个符号
// 这里用 ()、[]、{}
struct Paren {
  char left;
  char right;
  Paren(char l, char r) : left(l), right(r) {}
};

char findFriends(char a) {
  char result;
  if (a == '(')
    result = ')';
  else if (a == '[')
    result = ']';
  else
    result = '}';
  return result;
}

bool parenPlus(char expr[], int low, int high) {
  Stack<char> S;
  Paren small('(', ')');
  Paren middle('[', ']');
  Paren big('{', '}');

  for (int i = low; i < high; ++i) {
    if (expr[i] == small.left || expr[i] == middle.left || expr[i] == big.left)
      S.push(expr[i]);
    else {
      if (expr[i] != findFriends(S.top()))
        return false;
      else
        S.pop();
    }
  }
  return S.empty();
}
