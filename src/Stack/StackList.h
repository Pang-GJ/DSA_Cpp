#ifndef STACKLIST_H_
#define STACKLIST_H_

#include "../List/List.h"

template <typename T>
class Stack : public List<T> {
  // push pop top
  T top() const {
    return this->last()->data;
  }

  T pop() {
    return this->remove(this->last());
  }

  void push(const T &e) {
    this->insertAsLast(e);
  }
};

#endif