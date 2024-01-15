#pragma once
#include <string>
#include <unordered_map>

enum TokenType {
  // single character fellows
  L_PAREN,
  R_PAREN,
  L_BRACE,
  R_BRACE,
  MINUS,
  PLUS,
  ASTERISK,

  // one/two character fellows
  SLASH,
  BANG,
  BANG_EQUAL,
  EQUAL_EQUAL,
  GREATER,
  GREATER_EQUAL,
  LESS,
  LESS_EQUAL,

  // literals
  STRING,
  NUMBER,

  // keywords!!
  PUSH,
  POP,
  EJECT,
  INJECT,
  DUMP,
  EJECTREG,
  POPREG,
  PLEASE,
  PUT,
  ONTO,
  FROM,
  GET,
  STDOUT,
  STDIN,
  IF,
  OR,
  AND,

  _EOF,
};

static std::unordered_map<std::string, TokenType> keywords = {
  { "push", PUSH },
  { "pop", POP },
  { "eject", EJECT },
  { "inject", INJECT },
  { "dump", DUMP},
  { "ejectreg", EJECTREG },
  { "popreg", POPREG },
  { "please", PLEASE },
  { "put", PUT },
  { "onto", ONTO },
  { "from", FROM },
  { "get", GET },
  { "stdout", STDOUT },
  { "stdin", STDIN },
  { "or", OR },
  { "and", AND },
  { "if", IF },
};

class Token {
public:
  TokenType type;
  std::string lexeme;
  int line;
  std::string literal;

  Token(TokenType type, std::string lexeme, int line, std::string literal = "");
  Token();

  std::string toString();
};