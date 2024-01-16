#include "parser.hpp"
#include <iostream>

std::unique_ptr<Expr> Parser::expression() {
  return equality();
}

/**
 * @brief Parses an equality expression.
 * @return A unique_ptr to the returned expression.
 */
std::unique_ptr<Expr> Parser::equality() {
  std::unique_ptr<Expr> expr = comparison();

  while (match({ BANG_EQUAL, EQUAL_EQUAL })) {
    Token _operator = previous();
    std::unique_ptr<Expr> right = comparison();
    std::unique_ptr<Binary> binary(new Binary(std::move(expr), _operator, std::move(right)));
    expr = std::move(binary);
  }

  return expr;
}


std::unique_ptr<Expr> Parser::comparison() {
  std::unique_ptr<Expr> expr = term();

  while (match({ GREATER, GREATER_EQUAL, LESS, LESS_EQUAL })) {
    Token _operator = previous();
    std::unique_ptr<Expr> right = term();
    std::unique_ptr<Binary> binary(new Binary(std::move(expr), _operator, std::move(right)));
    expr = std::move(binary);
  }

  return expr;
}

std::unique_ptr<Expr> Parser::term() {
  std::unique_ptr<Expr> expr = unary();

  while (match({ MINUS, PLUS })) {
    Token _operator = previous();
    std::unique_ptr<Expr> right = factor();
    std::unique_ptr<Binary> binary(new Binary(std::move(expr), _operator, std::move(right)));
    expr = std::move(binary);
  }

  return expr;
}

std::unique_ptr<Expr> Parser::factor() {
  std::unique_ptr<Expr> expr = unary();

  while (match({ SLASH, ASTERISK })) {
    Token _operator = previous();
    std::unique_ptr<Expr> right = unary();
    std::unique_ptr<Binary> binary(new Binary(std::move(expr), _operator, std::move(right)));
    expr = std::move(binary);
  }

  return expr;
}

std::unique_ptr<Expr> Parser::unary() {
  if (match({ BANG, MINUS })) {
    Token _operator = previous();
    std::unique_ptr<Expr> right = unary();
    std::unique_ptr<Unary> unary(new Unary(_operator, std::move(right)));
    return std::move(unary);
  }

  return primary();
}

std::unique_ptr<Expr> Parser::primary() {
  if (match({ NUMBER, STRING })) {
    std::unique_ptr<Literal> literal(new Literal(previous().literal));
    return literal;
  }

  return nullptr;
}

std::unique_ptr<Expr> Parser::parse() {
  return expression();
}

bool Parser::match(std::initializer_list<TokenType> types) {
  for (TokenType type : types) {
    if (check(type)) {
      advance();
      return true;
    }
  }

  return false;
}

bool Parser::check(TokenType type) {
  if (isAtEnd()) return false;
  return peek().type == type;
}

Token Parser::advance() {
  if (!isAtEnd()) current++;
  return previous();
}

bool Parser::isAtEnd() {
  return peek().type == _EOF;
}

Token Parser::peek() {
  return tokens[current];
}

Token Parser::previous() {
  return tokens[current - 1];
}