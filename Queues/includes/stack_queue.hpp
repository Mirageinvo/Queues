#ifndef QUEUES_INCLUDES_STACK_QUEUE
#define QUEUES_INCLUDES_STACK_QUEUE

#include "Stack/Stack.hpp"
#include "Stack/Stack_impl.hpp"

namespace stack_queue {

    template<typename T>
    class Queue {
      public:
        Queue();
        Queue(const Queue& another);
        Queue(Queue&& another) noexcept;
        ~Queue() = default;

        void push(T el);
        T pop();
        const T& front() const;
        const T& back() const;
        size_t size() const;
        bool is_empty() const;

        bool operator==(const Queue& another) const;
        bool operator!=(const Queue& another) const;
        Queue& operator=(const Queue& another);
        Queue& operator=(Queue&& another) noexcept;

      private:
        void move_to_st2();
        Stack<T> st1_;
        Stack<T> st2_;
        size_t counter_;
    };

} //namespace stack_queue

#endif //QUEUES_INCLUDES_STACK_QUEUE