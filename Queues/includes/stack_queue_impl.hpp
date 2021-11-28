#ifndef QUEUES_INCLUDES_STACK_QUEUE_IMPL
#define QUEUES_INCLUDES_STACK_QUEUE_IMPL

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
void Queue<T>::push(T el) {
    st1_.push(el);
}








} //namespace stack_queue

#endif //QUEUES_INCLUDES_STACK_QUEUE_IMPL