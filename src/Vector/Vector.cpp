#include "Vector.h"
#include <algorithm>

#define DEFAULT_CAPACITY 3  // 默认初始容量

// 以数组区间 A[low, high) 为蓝本复制向量
template <typename T>
void Vector<T>::copyFrom(T const *A, Rank low, Rank high) {
  _elem = new T[_capacity = std::max(2 * (high - low), DEFAULT_CAPACITY)];
  _size = 0;
  while (low < high) {
    _elem[_size++] = A[low++];
  }
}