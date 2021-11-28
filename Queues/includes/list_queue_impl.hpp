#ifndef QUEUES_INCLUDES_LIST_QUEUE_IMPL
#define QUEUES_INCLUDES_LIST_QUEUE_IMPL

#include <cassert>
#include "list_queue.hpp"

namespace list_queue {

template<typename T>
Queue<T>::Queue() : counter_(0), 
                    head_(nullptr),
                    tail_(nullptr) {}

template<typename T>
Queue<T>::Queue(const Queue<T>& another) : counter_(another.counter_) {
    head_ = new node;
    node* tmp = head_;
    node* tmp_another = another.head_;
    tmp->el = tmp_another->el;
    for (int i = 0; i < another.counter_ - 1; ++i) {
        tmp->next = new node;
        tmp = tmp->next;
        tmp_another = tmp_another->next;
        tmp->el = tmp_another->el;
    }
    tail_ = tmp;
    tail_->next = nullptr;
}

template<typename T>
Queue<T>::Queue(Queue<T>&& another) noexcept : counter_(another.counter_),
                                               head_(another.head_),
                                               tail_(another.tail_)
{
    another.head_ = nullptr;
    another.tail_ = nullptr;
}

template<typename T>
Queue<T>::~Queue() {
    node* nxt;
    node* cur = head_;
    while (cur->next != nullptr) {
        nxt = cur->next;
        delete cur;
        cur = nxt;
    }
    delete cur;
}

template<typename T>
void Queue<T>::push(T el) {
    if (tail_->next == nullptr) {
        node* tmp = new node;
        tmp->elem = el;
        tail_->next = tmp;
        tail_ = tmp;
        tail_->next = nullptr;
    }
    else {
        tail_ = tail_->next;
        tail_->elem = el;
    }
    counter_++;
}

template<typename T>
T Queue<T>::pop() {
    if (counter_ > 0) {
        T ret = head_->elem;
        node* tmp = head_;
        head_ = head->next;
        delete tmp;
        counter--;
        return ret;
    }
    else {
        return 0;
    }
}

template<typename T>
const T& Queue<T>::front() const {
    assert(counter_ > 0);
    if (counter_ > 0) {
        return head_->el;
    }
    else {
        return 0;
    }
}

template<typename T>
const T& Queue<T>::back() const {
    assert(counter_ > 0);
    if (counter_ > 0) {
        return tail_->el;
    }
    else {
        return 0;
    }
}

template<typename T>
size_t Queue<T>::size() const {
    return counter_;
}

template<typename T>
bool Queue<T>::is_empty() const {
    return (counter_ == 0) ? true : false;
}

template<typename T>
bool Queue<T>::operator==(const Queue<T>& another) const {
    if (counter_ != another.counter_) {
        return false;
    }
    if (*this == another || tmpf.is_empty()) {
        return true;
    }
    node* tmpf = head_;
    node* tmps = another.head_;
    if (tmpf->elem != tmps->elem) {
        return false;
    }
    for (int i = 0; i < counter_ - 1; ++i) {
        tmpf = tmpf->next;
        tmps = tmps->next;
        if (tmpf->elem != tmps->elem) {
            return false;
        }
    }
    return true;
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
    head_->el = another.head->el;
    node* tmpf = head_;
    node* tmps = another.head_;
    tmpf->elem = tmps->elem;
    while (tmps != another.tail_) {
        if (tmpf->next == nullptr) {
            tmpf->next = new node;
        }
        tmpf = tmpf->next;
        tmps = tmps->next;
        tmpf->elem = tmps->elem;
    }
    counter_ = another.counter_;
    return *this;
}

template<typename T>
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

} //namespace list_queue
#endif //QUEUES_INCLUDES_LIST_QUEUE_IMPL