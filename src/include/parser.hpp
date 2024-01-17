#pragma once
#include "token.hpp"
#include "Loam.hpp"
#include "Expr.hpp"
#include <memory>
#include <vector>
#include <initializer_list>

class Parser {
private:
  std::vector<Token> tokens;
  int current = 0;

  bool match(std::initializer_list<TokenType> types);
  bool check(TokenType type);
  Token advance();
  bool isAtEnd();
  Token peek();
  Token consume(TokenType type, std::string message);
  Token previous();
  std::unique_ptr<Expr> expression();
  std::unique_ptr<Expr> equality();
  std::unique_ptr<Expr> comparison();
  std::unique_ptr<Expr> term();
  std::unique_ptr<Expr> factor();
  std::unique_ptr<Expr> unary();
  std::unique_ptr<Expr> primary();


public:
  Parser(std::vector<Token> tokens) {
    this->tokens = tokens;
  }

  std::unique_ptr<Expr> parse();
};