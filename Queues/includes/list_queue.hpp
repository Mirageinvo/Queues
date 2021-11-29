#ifndef QUEUES_INCLUDES_LIST_QUEUE
#define QUEUES_INCLUDES_LIST_QUEUE

namespace list_queue {

  template<typename T>
  struct node {
    T elem;
    node<T>* next;
  };

  template<typename T>
  class Queue {
      public:
        Queue();
        Queue(const Queue& another);
        Queue(Queue&& another) noexcept;
        ~Queue();

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
        size_t counter_;
        node<T>* head_;
        node<T>* tail_;
  };

} //namespace list_queue

#endif //QUEUES_INCLUDES_LIST_QUEUE