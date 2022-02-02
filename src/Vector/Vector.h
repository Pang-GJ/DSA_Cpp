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

#endif