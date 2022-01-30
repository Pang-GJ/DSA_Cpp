#include "Vector.h"

#include <cstdlib>
#include <ctime>

#define DEFAULT_CAPACITY 3  // 默认初始容量

template <typename T>
T max(T t1, T t2) {
  return t1 > t2 ? t1 : t2;
}

// 以数组区间 A[low, high) 为蓝本复制向量
template <typename T>
void Vector<T>::copyFrom(T const *A, Rank low, Rank high) {
  _elem = new T[_capacity = max(2 * (high - low), DEFAULT_CAPACITY)];
  _size = 0;
  while (low < high) {
    _elem[_size++] = A[low++];
  }
}

// 动态扩容，采用倍增策略
template <typename T>
void Vector<T>::expand() {
  if (_size < _capacity) return;

  _capacity = max(_capacity, DEFAULT_CAPACITY);
  T *_oldElem = _elem;
  _elem = new T[_capacity <<= 1];  // 左移 1 位，相当于 2倍增
  for (int i = 0; i < _size; ++i) _elem[i] = _oldElem[i];

  delete[] _oldElem;
}

// 下标随机访问
template <typename T>
T &Vector<T>::operator[](Rank r) {
  return _elem[r];
}

// 插入
template <typename T>
Rank Vector<T>::insert(Rank r, const T &e) {
  expand();  // 如果有必要，扩容
  for (Rank i = _size; i > r; --i) {
    _elem[i] = _elem[i - 1];
  }
  _elem[r] = e;
  _size++;
  return r;
}

// 区间删除
template <typename T>
int Vector<T>::remove(Rank low, Rank high) {
  if (low == high) return 0;

  while (high < _size) _elem[low++] = _elem[high++];

  _size = low;

  // shrink();  // 减少不必要的空间
  return high - low;  // 返回删除区间长度
}

// 单元素删除
template <typename T>
T Vector<T>::remove(Rank r) {
  T e = _elem[r];
  remove(r, r + 1);
  return e;  // 返回被删除元素
}

// 顺序查找
template <typename T>
Rank Vector<T>::find(const T &e, Rank low, Rank high) const {
  while (low < high-- && _elem[high] != e)
    ;           // 逆向查找
  return high;  // 多个命中则返回秩最大者，
}

// 无序向量去重
template <typename T>
int Vector<T>::deduplicate() {
  int oldSize = _size;
  Rank i = 0;
  while (i < _size) {
    if (find(_elem[i], 0, i) < 0)
      ++i;
    else
      remove(i);
  }
  return oldSize - _size;
}

// 借助函数指针的遍历接口
template <typename T>
void Vector<T>::traverse(void (*visit)(T &)) {
  for (Rank i = 0; i < _size; ++i) {
    visit(_elem[i]);
  }
}

// 借助函数对象的遍历接口
template <typename T>
template <typename VST>
void Vector<T>::traverse(VST &visit) {
  for (Rank i = 0; i < _size; ++i) {
    visit(_elem[i]);
  }
}

template <typename T>
int Vector<T>::disordered() const {
  int cnt = 0;  // 相邻逆序对的计数器
  for (int i = 1; i < _size; ++i) {
    if (_elem[i - 1] < _elem[i]) cnt++;
  }
  return cnt;
}

template <typename T>
int Vector<T>::uniquify() {
  Rank i = 0, j = 0;
  while (++j < _size) {
    if (_elem[i] != _elem[j]) _elem[++i] = _elem[j];
  }
  ++_size;
  // shrink();  // 减少不必要的空间
  return j - i;
}

template <typename T>
Rank Vector<T>::search(const T &e, Rank low, Rank high) const {
  return binSearch(_elem, e, low, high);
}

template <typename T>
void Vector<T>::sort(Rank low, Rank high) {
  switch (rand() % 6) {
    case 1:
      bubbleSort(low, high);
      break;
    case 2:
      selectionSort(low, high);
      break;
    case 3:
      mergeSort(low, high);
      break;
    case 4:
      heapSort(low, high);
      break;
    case 5:
      quickSort(low, high);
      break;
    default:
      shellSort(low, high);
      break;
  }
}