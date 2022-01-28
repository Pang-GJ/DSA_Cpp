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

// 动态扩容，采用倍增策略
template <typename T>
void Vector<T>::expand() {
  if (_size < _capacity) return;

  _capacity = std::max(_capacity, DEFAULT_CAPACITY);
  T *_oldElem = _elem;
  _elem = new T[_capacity <<= 1];   // 左移 1 位，相当于 2倍增
  for (int i = 0; i < _size; ++i) _elem[i] = _oldElem[i];

  delete[] _oldElem;
}