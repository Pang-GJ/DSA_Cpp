#ifndef STACKVECTOR_H_
#define STACKVECTOR_H_

#include "../Vector/Vector.h"

template <typename T>
class Stack : public Vector<T> {
 public:
  // push pop top
  Stack() = default;
  T pop() {
    return this->remove(this->size() - 1);
  }

  T top() const {
    return (*this)[this->size() - 1];
  } 

  void push(const T &e) {
    this->insert(this->size(), e);
  }
};

#endif