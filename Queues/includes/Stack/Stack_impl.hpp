#ifndef INCLUDES_STACK_IMPL
#define INCLUDES_STACK_IMPL

#include <algorithm>
#include <cassert>
#include <utility>

#include "Stack.hpp"

template <typename T>
Stack<T>::Stack(double grow_factor)
    : data_(new T[START_CAPACITY]),
      capacity_(START_CAPACITY),
      counter_(0),
      grow_factor_(grow_factor) {}

template <typename T>
Stack<T>::Stack(const Stack<T>& another) {
  data_ = new T[another.capacity_];
  capacity_ = another.capacity_;
  counter_ = another.counter_;
  grow_factor_ = another.grow_factor_;
  std::copy(another.data_, another.data_ + another.counter_, data_);
}

template <typename T>
Stack<T>::Stack(Stack&& another)
    : data_(another.data_),
      capacity_(another.capacity_),
      counter_(another.counter_),
      grow_factor_(another.grow_factor_) {
  another.data_ = nullptr;
  another.capacity_ = another.counter_ = 0;
}

template <typename T>
Stack<T>::~Stack() {
  delete[] data_;
}

template <typename T>
bool Stack<T>::is_empty() const {
  return counter_ == 0 ? true : false;
}

template <typename T>
size_t Stack<T>::size() const {
  return counter_;
}

template <typename T>
const T& Stack<T>::top() const {
  assert(counter_ != 0);
  return data_[counter_ - 1];
}

template <typename T>
T Stack<T>::pop() {
  assert(counter_ != 0);
  return data_[--counter_];
}

template <typename T>
void Stack<T>::stack_resize() {
  T* tmp = data_;
  data_ =
      new T[static_cast<size_t>(static_cast<double>(capacity_) * grow_factor_)];
  std::copy(tmp, tmp + counter_, data_);
  capacity_ =
      static_cast<size_t>(static_cast<double>(capacity_) * grow_factor_);
  delete[] tmp;
}

template <typename T>
void Stack<T>::push(T el) {
  if (counter_ == capacity_) {
    stack_resize();
  }
  data_[counter_++] = el;
}

template <typename T>
void Stack<T>::swap(Stack* another) {
  if (another != nullptr && another != this) {
    Stack tmp = std::move(*this);
    *this = std::move(*another);
    *another = std::move(tmp);
  }
}

template <typename T>
bool Stack<T>::operator==(const Stack<T>& another) const {
  if (counter_ != another.counter_) return false;
  for (size_t i = 0; i < counter_; ++i) {
    if (data_[i] != another.data_[i]) {
      return false;
    }
  }
  return true;
}

template <typename T>
bool Stack<T>::operator!=(const Stack<T>& another) const {
  return !(*this == another);
}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& another) {
  if (this == &another) {
    return *this;
  }
  delete[] data_;
  capacity_ = another.capacity_;
  counter_ = another.counter_;
  grow_factor_ = another.grow_factor_;
  data_ = new T[capacity_];
  std::copy(another.data_, another.data_ + another.counter_, data_);
  return *this;
}

template <typename T>
Stack<T>& Stack<T>::operator=(Stack<T>&& another) {
  if (this == &another) {
    return *this;
  }
  delete[] data_;
  capacity_ = another.capacity_;
  counter_ = another.counter_;
  data_ = another.data_;
  grow_factor_ = another.grow_factor_;
  another.data_ = nullptr;
  another.capacity_ = another.counter_ = 0;
  return *this;
}

Stack<bool>::Stack(double grow_factor)
    : data_(new uint32_t[START_INT_NUM]),
      capacity_(START_INT_NUM * sizeof(uint32_t) * 8),
      counter_(0),
      grow_factor_(grow_factor) {}

Stack<bool>::Stack(const Stack<bool>& another) {
  data_ = new uint32_t[1 + another.capacity_ / sizeof(uint32_t) / 8];
  capacity_ = another.capacity_;
  counter_ = another.counter_;
  grow_factor_ = another.grow_factor_;
  std::copy(another.data_,
            another.data_ + (another.counter_ / sizeof(uint32_t) / 8) + 1,
            data_);
}

Stack<bool>::Stack(Stack<bool>&& another)
    : data_(another.data_),
      capacity_(another.capacity_),
      counter_(another.counter_),
      grow_factor_(another.grow_factor_) {
  another.data_ = nullptr;
  another.capacity_ = another.counter_ = 0;
}

Stack<bool>::~Stack() { delete[] data_; }

size_t Stack<bool>::size() const { return counter_; }

bool Stack<bool>::is_empty() const { return counter_ == 0 ? true : false; }

bool Stack<bool>::top() const {
  assert(counter_ != 0);
  return (data_[(counter_ - 1) / sizeof(uint32_t) / 8] &
          (1u << ((counter_ - 1) % (sizeof(uint32_t) * 8))));
}

bool Stack<bool>::pop() {
  assert(counter_ != 0);
  counter_--;
  uint32_t tmp = (1 << (counter_ % (sizeof(uint32_t) * 8)));
  bool ret = (data_[counter_ / sizeof(uint32_t) / 8] & tmp);
  data_[counter_ / sizeof(uint32_t) / 8] =
      data_[counter_ / sizeof(uint32_t) / 8] & (~tmp);
  return ret;
}

void Stack<bool>::stack_resize() {
  uint32_t* tmp = data_;
  data_ = new uint32_t[static_cast<size_t>(
      static_cast<double>(1 + capacity_ / sizeof(uint32_t) / 8) *
      grow_factor_)];
  std::copy(tmp, tmp + (counter_ / sizeof(uint32_t) / 8), data_);
  capacity_ =
      static_cast<size_t>(static_cast<double>(capacity_) * grow_factor_);
  delete[] tmp;
}

void Stack<bool>::push(bool el) {
  if (counter_ == capacity_) {
    stack_resize();
  }
  data_[counter_ / sizeof(uint32_t) / 8] =
      data_[counter_ / sizeof(uint32_t) / 8] &
      (~(1u << (counter_ % (sizeof(uint32_t) * 8))));
  if (el) {
    data_[counter_ / sizeof(uint32_t) / 8] =
        data_[counter_ / sizeof(uint32_t) / 8] |
        (1u << (counter_ % (sizeof(uint32_t) * 8)));
  }
  counter_++;
}

void Stack<bool>::swap(Stack<bool>* another) {
  if (another != nullptr && another != this) {
    Stack<bool> tmp = std::move(*this);
    *this = std::move(*another);
    *another = std::move(tmp);
  }
}

bool Stack<bool>::operator==(const Stack<bool>& another) const {
  if (counter_ != another.counter_) {
    return false;
  }
  for (size_t i = 0; i < counter_; ++i) {
    if (data_[counter_ / sizeof(uint32_t) / 8] !=
        another.data_[counter_ / sizeof(uint32_t) / 8]) {
      return false;
    }
  }
  return true;
}

bool Stack<bool>::operator!=(const Stack<bool>& another) const {
  return !(*this == another);
}

Stack<bool>& Stack<bool>::operator=(const Stack<bool>& another) {
  if (this == &another) {
    return *this;
  }
  delete[] data_;
  capacity_ = another.capacity_;
  counter_ = another.counter_;
  data_ = new uint32_t[1 + capacity_ / sizeof(uint32_t) / 8];
  std::copy(another.data_,
            another.data_ + (another.counter_ / sizeof(uint32_t) / 8) + 1,
            data_);
  return *this;
}

Stack<bool>& Stack<bool>::operator=(Stack<bool>&& another) {
  if (this == &another) {
    return *this;
  }
  delete[] data_;
  capacity_ = another.capacity_;
  counter_ = another.counter_;
  data_ = another.data_;
  grow_factor_ = another.grow_factor_;
  another.data_ = nullptr;
  another.capacity_ = another.counter_ = 0;
  another.grow_factor_ = 0.0;
  return *this;
}
#endif  // INCLUDES_STACK_IMPL