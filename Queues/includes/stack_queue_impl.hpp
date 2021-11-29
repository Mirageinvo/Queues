#ifndef QUEUES_INCLUDES_STACK_QUEUE_IMPL
#define QUEUES_INCLUDES_STACK_QUEUE_IMPL

#include <cassert>
#include "stack_queue.hpp"

namespace stack_queue {

template<typename T>
Queue<T>::Queue() : counter_(0) {}

template<typename T>
Queue<T>::Queue(const Queue& another) : counter_(another.counter_),
                                        st1_(another.st1_),
                                        st2_(another.st2_) {}

template<typename T>
Queue<T>::Queue(Queue&& another) noexcept : counter_(another.counter_),
                                            st1_(std::move(another.st1_)),
                                            st2_(std::move(another.st2_)) {}

template<typename T>
void Queue<T>::move_to_st2() {
    assert(!st1_.is_empty() && st2_.is_empty());
    if (st1_.size() > 1) {
        while (st1_.size() > 1) {
            st2_.push(st1_.pop());
        }
    }
    else if (st1_.size() > 1) {
        st2_.push(st1_.pop());
    }
}

template<typename T>
void Queue<T>::push(T el) {
    st1_.push(el);
    counter_++;
}

template<typename T>
T Queue<T>::pop() {
    assert(counter_ > 0);
    if (counter_ > 0) {
        if (st2_.is_empty()) {
            move_to_st2();
        }
        counter_--;
        return st2_.pop();
    }
    else {
        return 0;
    }
}

template<typename T>
const T& Queue<T>::front() const {
    assert(counter_ > 0);
    if (st2_.is_empty()) {
        move_to_st2();
    }
    return st2_.top();
}

template<typename T>
const T& Queue<T>::back() const {
    assert(counter_ > 0 && st1_.size() > 0);
    return st1_.top();
}

template<typename T>
size_t Queue<T>::size() const {
    assert(counter_ == st1_.size() + st2_.size());
    return counter_;
}

template<typename T>
bool Queue<T>::is_empty() const {
    assert(counter_ == st1_.size() + st2_.size());
    return (counter_ == 0) ? true : false;
}

template<typename T>
bool Queue<T>::operator==(const Queue<T>& another) const {
    if (counter_ != another.counter_) {
        return false;
    }
    return st1_ == another.st1_ && st2_ == another.st2_;
}

template<typename T>
bool Queue<T>::operator!=(const Queue<T>& another) const {
    return !(*this == another);
}

template<typename T>
Queue<T>& Queue<T>::operator=(const Queue<T>& another) {
    if (this == &another) {
        return *this;
    }
    st1_ = another.st1_;
    st2_ = another.st2_;
    counter_ = another.counter_;
    return *this;
}

template<typename T>
Queue<T>& Queue<T>::operator=(Queue<T>&& another) noexcept {
    if (this == &another) {
        return *this;
    }
    st1_ = std::move(another.st1_);
    st2_ = std::move(another.st2_);
    counter_ = another.counter_;
    return *this;
}

} //namespace stack_queue
#endif //QUEUES_INCLUDES_STACK_QUEUE_IMPL