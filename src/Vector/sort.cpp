#include "Vector.h"

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