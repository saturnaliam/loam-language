#include "token.hpp"
#include <string>

class Expr {};

class Binary : protected Expr {
  Binary(Expr left, Token _operator, Expr right) {
    this->left = left;
    this->_operator = _operator;
    this->right = right;
  }

  Expr left;
  Token _operator;
  Expr right;
};

class Grouping : protected Expr {
  Grouping(Expr expression) {
    this->expression = expression;
  }

  Expr expression;
};

class Literal : protected Expr {
  Literal(std::string value) {
    this->value = value;
  }

  std::string value;
};

class Unary : protected Expr {
  Unary(Token _operator, Expr right) {
    this->_operator = _operator;
    this->right = right;
  }

  Token _operator;
  Expr right;
};

