#ifndef QUEUES_INCLUDES_LIST_QUEUE_IMPL
#define QUEUES_INCLUDES_LIST_QUEUE_IMPL

#include <cassert>

#include "list_queue.hpp"

namespace list_queue {

template <typename T>
Queue<T>::Queue() : counter_(0), head_(nullptr), tail_(nullptr) {}

template <typename T>
Queue<T>::Queue(const Queue<T>& another) : counter_(another.counter_) {
  head_ = new node<T>;
  node<T>* tmp = head_;
  node<T>* tmp_another = another.head_;
  tmp->elem = tmp_another->elem;
  for (int i = 0; i < static_cast<int>(another.counter_) - 1; ++i) {
    tmp->next = new node<T>;
    tmp = tmp->next;
    tmp_another = tmp_another->next;
    tmp->elem = tmp_another->elem;
  }
  tail_ = tmp;
  tail_->next = nullptr;
}

template <typename T>
Queue<T>::Queue(Queue<T>&& another) noexcept
    : counter_(another.counter_), head_(another.head_), tail_(another.tail_) {
  another.head_ = nullptr;
  another.tail_ = nullptr;
}

template <typename T>
Queue<T>::~Queue() {
  if (head_ != nullptr) {
    node<T>* nxt;
    node<T>* cur = head_;
    while (cur->next != nullptr) {
      nxt = cur->next;
      delete cur;
      cur = nxt;
    }
    delete cur;
  }
}

template <typename T>
void Queue<T>::push(T el) {
  if (is_empty()) {
    head_ = new node<T>;
    head_->elem = el;
    head_->next = nullptr;
    tail_ = head_;
  } else {
    if (tail_->next == nullptr) {
      node<T>* tmp = new node<T>;
      tmp->elem = el;
      tail_->next = tmp;
      tail_ = tmp;
      tail_->next = nullptr;
    } else {
      tail_ = tail_->next;
      tail_->elem = el;
    }
  }
  counter_++;
}

template <typename T>
T Queue<T>::pop() {
  if (counter_ == 1) {
    T ret = head_->elem;
    delete head_;
    head_ = nullptr;
    tail_ = nullptr;
    counter_ = 0;
    return ret;
  } else if (counter_ > 1) {
    T ret = head_->elem;
    node<T>* tmp = head_;
    head_ = head_->next;
    delete tmp;
    counter_--;
    return ret;
  } else {
    exit(-1);
  }
}

template <typename T>
const T& Queue<T>::front() const {
  assert(counter_ > 0);
  if (counter_ > 0) {
    return head_->elem;
  } else {
    exit(-1);
  }
}

template <typename T>
const T& Queue<T>::back() const {
  assert(counter_ > 0);
  if (counter_ > 0) {
    return tail_->elem;
  } else {
    exit(-1);
  }
}

template <typename T>
size_t Queue<T>::size() const {
  return counter_;
}

template <typename T>
bool Queue<T>::is_empty() const {
  return (counter_ == 0) ? true : false;
}

template <typename T>
bool Queue<T>::operator==(const Queue<T>& another) const {
  if (counter_ != another.counter_) {
    return false;
  }
  if (this == &another || counter_ == 0) {
    return true;
  }
  node<T>* tmpf = head_;
  node<T>* tmps = another.head_;
  if (tmpf->elem != tmps->elem) {
    return false;
  }
  for (int i = 0; i < static_cast<int>(counter_) - 1; ++i) {
    tmpf = tmpf->next;
    tmps = tmps->next;
    if (tmpf->elem != tmps->elem) {
      return false;
    }
  }
  return true;
}

template <typename T>
bool Queue<T>::operator!=(const Queue<T>& another) const {
  return !(*this == another);
}

template <typename T>
Queue<T>& Queue<T>::operator=(const Queue<T>& another) {
  if (this == &another) {
    return *this;
  }
  if (another.counter_ == 0 || another.head_ == nullptr) {
    counter_ = 0;
    tail_ = nullptr;
    head_ = nullptr;
  }
  if (head_ == nullptr) {
    head_ = new node<T>;
    head_->next = nullptr;
  }
  head_->elem = another.head_->elem;
  node<T>* tmpf = head_;
  node<T>* tmps = another.head_;
  while (tmps != another.tail_) {
    if (tmpf->next == nullptr) {
      tmpf->next = new node<T>;
      tmpf->next->next = nullptr;
    }
    tmpf = tmpf->next;
    tmps = tmps->next;
    tmpf->elem = tmps->elem;
  }
  counter_ = another.counter_;
  return *this;
}

template <typename T>
Queue<T>& Queue<T>::operator=(Queue<T>&& another) noexcept {
  if (this == &another) {
    return *this;
  }
  head_ = another.head_;
  tail_ = another.tail_;
  counter_ = another.counter_;
  another.head_ = nullptr;
  another.tail_ = nullptr;
  return *this;
}

}  // namespace list_queue
#endif  // QUEUES_INCLUDES_LIST_QUEUE_IMPL