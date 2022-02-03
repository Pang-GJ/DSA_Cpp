// 中缀表达式求值
#include "../StackList.h"
#include <cctype>
#define N_OPTR 9

void readNumbers(char *, Stack<double> &);
char orderBetween(char, char);
double calcu(char, double);
double calcu(double, char, double);

// 代码自动格式化成这样了;
const char pri[N_OPTR][N_OPTR] = {
    '>', '>', '<', '<', '<', '<', '<', '>', '>', 
    '>', '>', '<', '<', '<', '<', '<', '>', '>', 
    '>', '>', '>', '>', '<', '<', '<', '>', '>', 
    '>', '>', '>', '>', '<', '<', '<', '>', '>', 
    '>', '>', '>', '>', '>', '<', '<', '>', '>', 
    '>', '>', '>', '>', '>', '>', ' ', '>', '>', 
    '<', '<', '<', '<', '<', '<', '<', '=', ' ', 
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 
    '<', '<', '<', '<', '<', '<', '<', ' ', '=',
};

float eveluate(char *S, char * & RPN) {
  Stack<double> opnd; Stack<char> optr;
  optr.push('\0');
  while (!optr.empty()) {
    if (std::isdigit(*S))
      readNumbers(S, opnd);
    else
     switch(orderBetween(optr.pop(), *S)) {
       case '<':
        optr.push(*S); S++; break;
       case '=':
        optr.pop(); S++; break;
       case '>': {
         char op = optr.pop();
         if ('!' == op) opnd.push(calcu(op, opnd.pop()));
         else {
           float pOpnd2 = opnd.pop();
           float pOpnd1 = opnd.pop(); 
           opnd.push(calcu(pOpnd1, op, pOpnd2));
         }
         break;
       }

     };
  }

  return opnd.pop();
}