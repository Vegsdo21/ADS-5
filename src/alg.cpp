// Copyright 2025 NNTU-CS
#include <string>
#include <sstream>
#include <cctype>
#include "tstack.h"

int precedence(char op) {
  if (op == '+' || op == '-') return 1;
  if (op == '*' || op == '/') return 2;
  return 0;
}

bool isOperator(char c) {
  return c == '+' || c == '-' || c == '*' || c == '/';
}

std::string infx2pstfx(const std::string& inf) {
  std::vector<std::string> tokens;
  TStack<char, 100> opStack;
  int i = 0;

  while (i < inf.length()) {
    if (isspace(inf[i])) {
      ++i;
      continue;
    }

    if (isdigit(inf[i])) {
      std::string number;
      while (i < inf.length() && isdigit(inf[i])) {
        number += inf[i++];
      }
      tokens.push_back(number);
    } else if (inf[i] == '(') {
      opStack.push(inf[i++]);
    } else if (inf[i] == ')') {
      while (!opStack.isEmpty() && opStack.peek() != '(') {
        tokens.push_back(std::string(1, opStack.pop()));
      }
      if (!opStack.isEmpty() && opStack.peek() == '(')
        opStack.pop();
      ++i;
    } else if (isOperator(inf[i])) {
      while (!opStack.isEmpty() &&
             precedence(opStack.peek()) >= precedence(inf[i])) {
        tokens.push_back(std::string(1, opStack.pop()));
      }
      opStack.push(inf[i++]);
    } else {
      ++i;  // skip unknown character
    }
  }

  while (!opStack.isEmpty()) {
    tokens.push_back(std::string(1, opStack.pop()));
  }

  std::ostringstream out;
  for (size_t j = 0; j < tokens.size(); ++j) {
    if (j > 0) out << ' ';
    out << tokens[j];
  }
  return out.str();
}

int eval(const std::string& pref) {
  std::istringstream in(pref);
  TStack<int, 100> st;
  std::string token;

  while (in >> token) {
    if (isdigit(token[0]) ||
        (token.length() > 1 && token[0] == '-')) {
      st.push(std::stoi(token));
    } else {
      int b = st.pop();
      int a = st.pop();
      if (token == "+") st.push(a + b);
      else if (token == "-") st.push(a - b);
      else if (token == "*") st.push(a * b);
      else if (token == "/") st.push(a / b);
    }
  }

  return st.pop();
}
