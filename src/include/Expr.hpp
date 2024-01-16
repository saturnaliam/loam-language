#pragma once
#include "token.hpp"
#include <string>
#include <memory>
#include <iostream>

class Expr {
public:
  virtual void hi() {};
};

class Binary : public Expr {
public:
  Binary(std::unique_ptr<Expr> left, Token _operator, std::unique_ptr<Expr> right) {
    this->left = std::move(left);
    this->_operator = _operator;
    this->right = std::move(right);
  }

  std::unique_ptr<Expr> left;
  Token _operator;
  std::unique_ptr<Expr> right;
};

class Grouping : public Expr {
public:
  Grouping(std::unique_ptr<Expr> expression) {
    this->expression = std::move(expression);
  }

  std::unique_ptr<Expr> expression;
};

class Literal : public Expr {
public:
  Literal(std::string value) {
    this->value = value;
  }

  void hi() {
    std::cout << "hi";
  }

  std::string value;
};

class Unary : public Expr {
public:
  Unary(Token _operator, std::unique_ptr<Expr> right) {
    this->_operator = _operator;
    this->right = std::move(right);
  }

  Token _operator;
  std::unique_ptr<Expr> right;
};