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
  std::string result;
  int i = 0;

  while (i < inf.size()) {
    if (std::isdigit(inf[i])) {
      while (i < inf.size() && std::isdigit(inf[i])) {
        result += inf[i++];
      }
      result += ' ';
    } else if (inf[i] == '(') {
      opStack.push('(');
      i++;
    } else if (inf[i] == ')') {
      while (!opStack.isEmpty() && opStack.peek() != '(') {
        result += opStack.pop();
        result += ' ';
      }
      if (!opStack.isEmpty()) opStack.pop();
      i++;
    } else if (inf[i] == '+' || inf[i] == '-' || inf[i] == '*' || inf[i] == '/') {
      while (!opStack.isEmpty() && getPriority(opStack.peek()) >= getPriority(inf[i])) {
        result += opStack.pop();
        result += ' ';
      }
      opStack.push(inf[i]);
      i++;
    } else {
      i++;
    }
  }

  while (!opStack.isEmpty()) {
    result += opStack.pop();
    result += ' ';
  }

  return result;
}

int eval(const std::string& post) {
  TStack<int, 100> valStack;
  int i = 0;

  while (i < post.size()) {
    if (std::isdigit(post[i])) {
      int number = 0;
      while (i < post.size() && std::isdigit(post[i])) {
        number = number * 10 + (post[i] - '0');
        i++;
      }
      valStack.push(number);
    } else if (post[i] == '+' || post[i] == '-' || post[i] == '*' || post[i] == '/') {
      int b = valStack.pop();
      int a = valStack.pop();
      int res = 0;
      switch (post[i]) {
        case '+': res = a + b; break;
        case '-': res = a - b; break;
        case '*': res = a * b; break;
        case '/': res = a / b; break;
      }
      valStack.push(res);
      i++;
    } else {
      i++;
    }
  }

  return valStack.pop();
}
