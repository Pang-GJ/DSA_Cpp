#ifndef QUEUELIST_H_
#define QUEUELIST_H_

#include "../List/List.h"

template <typename T>
class Queue : public List<T> {
  // dequeue, enqueue, front, rear
  T dequeue() {
    T e = this->first()->data;
    this->remove(this->first());
    return e;
  }

  void enqueue(const T &e) { this->insertAsLast(e); }

  T front() const { return this->first()->data; }

  T rear() const { return this->last()->data; }
};

#endif