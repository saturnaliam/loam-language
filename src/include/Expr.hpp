#pragma once
#include "token.hpp"
#include <string>
#include <memory>
#include <iostream>

enum ExpressionType {
  BINARY,
  GROUPING,
  LITERAL,
  UNARY,
};

class Expr {
public:
  ExpressionType expressionType;

  /**
   * @warning DO NOT USE. NOT IMPLEMENTED YET.
   */
  virtual void accept() {};
};

class Binary : public Expr {
public:
  Binary(std::unique_ptr<Expr> left, Token _operator, std::unique_ptr<Expr> right) {
    this->expressionType = BINARY;
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
    this->expressionType = GROUPING;
    this->expression = std::move(expression);
  }

  std::unique_ptr<Expr> expression;
};

class Literal : public Expr {
public:
  Literal(std::string value) {
    this->expressionType = LITERAL;
    this->value = value;
  }

  std::string value;
};

class Unary : public Expr {
public:
  Unary(Token _operator, std::unique_ptr<Expr> right) {
    this->expressionType = UNARY;
    this->_operator = _operator;
    this->right = std::move(right);
  }

  Token _operator;
  std::unique_ptr<Expr> right;
};