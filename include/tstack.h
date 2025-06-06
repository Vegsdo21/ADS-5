// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_
#include <stdexcept>

template<typename T, int size>
class TStack {
 private:
  static constexpr int kStackSize = size;
  T data[kStackSize];
  int top;

 public:
  TStack() : top(-1) {}

  void push(const T& val) {
    if (top >= kStackSize - 1)
      throw std::overflow_error("Stack overflow");
    data[++top] = val;
  }

  T pop() {
    if (top == -1)
      throw std::underflow_error("Stack underflow");
    return data[top--];
  }

  T peek() const {
    if (top == -1)
      throw std::underflow_error("Stack underflow");
    return data[top];
  }

  bool isEmpty() const {
    return top == -1;
  }
};

#endif  // INCLUDE_TSTACK_H_
