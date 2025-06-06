// Copyright 2025 NNTU-CS
#include <string>
#include <cctype>
#include <sstream> 
#include "tstack.h"

int getPriority(char op) {
  if (op == '+' || op == '-') return 1;
  if (op == '*' || op == '/') return 2;
  return 0;
}

std::string infx2pstfx(const std::string& inf) {
  TStack<char, 100> opStack;
  std::string res;
  int i = 0;

  while (i < inf.length()) {
    if (std::isdigit(inf[i])) {
      while (i < inf.length() && std::isdigit(inf[i])) {
        res += inf[i++];
      }
      res += ' ';
    } else if (inf[i] == '(') {
      opStack.push('(');
      i++;
    } else if (inf[i] == ')') {
      while (!opStack.isEmpty() && opStack.peek() != '(') {
        res += opStack.pop();
        res += ' ';
      }
      if (!opStack.isEmpty()) opStack.pop();  // убрать '('
      i++;
    } else if (inf[i] == '+' || inf[i] == '-' ||
               inf[i] == '*' || inf[i] == '/') {
      while (!opStack.isEmpty() &&
             getPriority(opStack.peek()) >= getPriority(inf[i])) {
        res += opStack.pop();
        res += ' ';
      }
      opStack.push(inf[i]);
      i++;
    } else {
      i++;
    }
  }

  while (!opStack.isEmpty()) {
    res += opStack.pop();
    res += ' ';
  }

  return res;
}

int eval(const std::string& post) {
  TStack<int, 100> stack;
  std::istringstream input(post);
  std::string token;

  while (input >> token) {
    if (std::isdigit(token[0])) {
      stack.push(std::stoi(token));
    } else {
      if (stack.isEmpty()) throw std::runtime_error("Stack underflow");
      int b = stack.pop();
      if (stack.isEmpty()) throw std::runtime_error("Stack underflow");
      int a = stack.pop();

      if (token == "+") stack.push(a + b);
      else if (token == "-") stack.push(a - b);
      else if (token == "*") stack.push(a * b);
      else if (token == "/") stack.push(a / b);
      else throw std::runtime_error("Unknown operator");
    }
  }

  if (stack.isEmpty()) throw std::runtime_error("Stack underflow");
  return stack.pop();
}
