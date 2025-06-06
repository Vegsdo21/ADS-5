// Copyright 2025 NNTU-CS
#include <string>
#include <cctype>
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
    if (std::isspace(inf[i])) {
      i++;
    } else if (std::isdigit(inf[i])) {
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
      if (!opStack.isEmpty()) opStack.pop();
      i++;
    } else if (inf[i] == '+' || inf[i] == '-' || inf[i] == '*' || inf[i] == '/') {
      while (!opStack.isEmpty() && getPriority(opStack.peek()) >= getPriority(inf[i])) {
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

  if (!res.empty() && res.back() == ' ')
    res.pop_back();

  return res;
}

int eval(const std::string& post) {
  TStack<int, 100> stack;
  int i = 0;

  while (i < post.length()) {
    if (std::isspace(post[i])) {
      i++;
    } else if (std::isdigit(post[i])) {
      int num = 0;
      while (i < post.length() && std::isdigit(post[i])) {
        num = num * 10 + (post[i] - '0');
        i++;
      }
      stack.push(num);
    } else if (post[i] == '+' || post[i] == '-' || post[i] == '*' || post[i] == '/') {
      int b = stack.pop();
      int a = stack.pop();
      if (post[i] == '+') stack.push(a + b);
      else if (post[i] == '-') stack.push(a - b);
      else if (post[i] == '*') stack.push(a * b);
      else if (post[i] == '/') stack.push(a / b);
      i++;
    } else {
      i++;
    }
  }

  return stack.pop();
}
