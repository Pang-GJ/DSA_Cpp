// 进制转换
#include <sys/types.h>

#include <cstdio>

#include "../StackVector.h"

void convert(Stack<char> &S, int n, int base) {
  static char digit[] = {'0', '1', '2', '3', '4', '5', '6', '7',
                         '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
  while (n > 0) {
    S.push(digit[n % base]);
    n /= base;
  }
}

int main(int argc, char *argv[]) {
  Stack<char> S;
  int n = 2013, base = 5;
  convert(S, n, base);
  while (!S.empty()) {
    printf("%c", S.pop());
  }

  return 0;
}