#ifndef VECTOR_H_
#define VECTOR_H_

#define DEFAULT_CAPACITY 3  // 默认初始容量

using Rank = int;  // 秩

template <typename T>
class Vector {
 private:
  Rank _size;
  int _capacity;
  T *_elem;

 protected:
  // 内部函数
  void copyFrom(T const *A, Rank low, Rank high);
  void expand();
  void bubbleSort(Rank low, Rank high);
  void selectionSort(Rank low, Rank high);
  void merge(Rank low, Rank mid, Rank high);
  void mergeSort(Rank low, Rank high);
  void heapSort(Rank low, Rank high);
  void quickSort(Rank low, Rank high);
  void shellSort(Rank low, Rank high);

 public:
  // 构造函数：
  // 默认
  Vector(int c = DEFAULT_CAPACITY) {
    _elem = new T[_capacity = c];
    _size = 0;
  }
  // 数组区间复制
  Vector(T const *A, Rank low, Rank high) { copyFrom(A, low, high); }
  // 向量区间复制
  Vector(Vector<T> const &V, Rank low, Rank high) {
    copyFrom(V._elem, low, high);
  }
  // 向量整体复制
  Vector(Vector<T> const &V) { copyFrom(V._elem, 0, V.size()); }

  // 析构函数:
  // 释放内部空间
  ~Vector() { delete[] _elem; }
  // 只读接口
  Rank find(const T &e, Rank low, Rank high) const;  // 顺序查找
  int disordered() const;  // 判断所有元素是否有序
  Rank search(const T &e, Rank low, Rank high) const;  // 有序向量查找
  int size() const { return _size; }
  bool empty() const { return _size == 0; }
  // 可写接口
  T &operator[](Rank r);            // 下标随机访问
  Rank insert(Rank r, const T &e);  // 插入
  int remove(Rank low, Rank high);  // 区间删除
  T remove(Rank r);                 // 单元素删除
  int deduplicate();                // 无序向量去重
  int uniquify();                   // 有序向量去重
  void sort(Rank low, Rank high);   // 排序算法

  // 遍历接口
  void traverse(void (*visit)(T &));  // 借助函数指针，只读或局部修改

  template <typename VST>
  void traverse(VST &visit);  // 借助函数对象机制，全局修改更便捷
};

// 供 traverse 使用的一些函数对象实例
// 加一
template <typename T>
struct Increase {
  virtual void operator()(T &e) { e++; }
};
// 减一
template <typename T>
struct Decrease {
  virtual void operator()(T &e) { e--; }
};
// 加倍
template <typename T>
struct Double {
  virtual void operator()(T &e) { e *= 2; }
};
// 求和
template <typename T>
struct Sum {
  static int sum;
  virtual void operator()(T &e) { sum += e; }
};

// int Sum::sum = 0;

// 二分查找算法
template <typename T>
static Rank binSearch(T *S, const T &e, Rank low, Rank high) {
  while (low < high) {
    Rank mid = low + ((high - low) >> 1);
    if (e < S[mid])
      low = mid + 1;
    else
      high = mid;
  }  // 出口时：必有 S[low] = s[high] = M
  return low - 1;
}

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

template <typename T>
void swap(T& a, T& b) {
  T temp = a;
  a = b;
  b = temp;
}

// 基本版冒泡排序
// template <typename T>
// void Vector<T>::bubbleSort(Rank low, Rank high) {
//   for (Rank i = low; i < high; ++i) {
//     for (Rank j = i; j < high; ++j) {
//       if (_elem[j] < _elem[i]) swap(_elem[i], _elem[j]);
//     }
//   }
// }

// 提前终止版冒泡排序
// template <typename T>
// void Vector<T>::bubbleSort(Rank low, Rank high) {
//   bool sorted = false;
//   while (!sorted) {
//     sorted = true;  // 假设这次会使所有元素排好序
//     for (Rank i = low; low < high - 1; low++) {
//       if (_elem[i] > _elem[i + 1]) {
//         swap(_elem[i], _elem[i + 1]);
//         sorted = false;
//       }
//     }
//   }
// }

// 跳跃版冒泡排序
template <typename T>
void Vector<T>::bubbleSort(Rank low, Rank high) {
  for (Rank last = high--; low < high; high = last) {
    for (Rank i = last = low; i < high; ++i) {
      if (_elem[i] > _elem[i + 1]) {
        swap(_elem[i], _elem[i + 1]);
        last = i;  // 逆序对只可能残留在 [low, last)
      }
    }
  }
}

// 选择排序
template <typename T>
void Vector<T>::selectionSort(Rank low, Rank high) {
  Rank maxElemIndex = 0;
  for (int i = low; i < high; ++i) {
    for (int j = i; j < high; ++j) {
      if (_elem[maxElemIndex] < _elem[j]) maxElemIndex = j;
    }
    swap(_elem[maxElemIndex], _elem[i]);
  }
}

// 归并排序
template <typename T>
void Vector<T>::mergeSort(Rank low, Rank high) {
  if (high - low < 2) return;

  Rank mid = low + ((high - low) >> 1);
  mergeSort(low, mid);
  mergeSort(mid, high);
  merge(low, mid, high);
}

template <typename T>
void Vector<T>::merge(Rank low, Rank mid, Rank high) {
  T* tempArray = new T[high - low + 1];
  Rank oldMid = mid, oldLow = low, i = 0;
  while (low < oldMid && mid < high) {
    tempArray[i++] = _elem[low] < _elem[mid] ? _elem[low++] : _elem[mid++];
  }

  while (low < oldMid) tempArray[i++] = _elem[low++];
  while (mid < high) tempArray[i++] = _elem[mid++];

  for (int j = 0; j < i; ++j) _elem[oldLow++] = tempArray[j];

  delete[] tempArray;
}

#endif