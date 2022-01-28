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
  Vector(Vector<T> const &V) { copyFrom(V._elem); }

  // 析构函数:
  // 释放内部空间
  ~Vector() { delete[] _elem; }
  // 只读接口
  // 可写接口
  // 遍历接口
};

#endif