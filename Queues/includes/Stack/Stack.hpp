#ifndef INCLUDES_STACK
#define INCLUDES_STACK

template <typename T>
class Stack {
 public:
  const size_t START_CAPACITY = 32;
  explicit Stack(double grow_factor = 2);
  Stack(const Stack& another);
  Stack(Stack&& another);
  ~Stack();

  size_t size() const;
  bool is_empty() const;
  const T& top() const;
  T pop();
  void push(T el);
  void swap(Stack* another);

  bool operator==(const Stack& another) const;
  bool operator!=(const Stack& another) const;
  Stack& operator=(const Stack& another);
  Stack& operator=(Stack&& another);

 private:
  T* data_;
  size_t capacity_;
  size_t counter_;
  double grow_factor_;
  void stack_resize();
};

template <>
class Stack<bool> {
 public:
  const size_t START_INT_NUM = 1;
  explicit Stack(double grow_factor = 2);
  Stack(const Stack& another);
  Stack(Stack&& another);
  ~Stack();

  size_t size() const;
  bool is_empty() const;
  bool top() const;
  bool pop();
  void push(bool el);
  void swap(Stack* another);

  bool operator==(const Stack& another) const;
  bool operator!=(const Stack& another) const;
  Stack& operator=(const Stack& another);
  Stack& operator=(Stack&& another);

 private:
  uint32_t* data_;
  size_t capacity_;
  size_t counter_;
  double grow_factor_;
  void stack_resize();
};

#endif  // INCLUDES_STACK