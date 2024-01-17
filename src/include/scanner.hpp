#pragma once
#include "token.hpp"
#include "Loam.hpp"
#include <string>
#include <vector>

class Scanner {
private:
  int line = 1;
  int current = 0;
  int start = 0;

  std::string source;
  std::vector<Token> tokens;

  bool isAtEnd();

  void scanToken();
  void addToken(TokenType type, std::string literal = "");

  void string();
  void number();
  bool identifier();

  bool match(char expected);
  char advance();
  char peek();
  char peekNext();

public:
  Scanner(std::string source);
  std::vector<Token> scanTokens();
};