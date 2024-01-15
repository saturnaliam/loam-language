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

  void scanToken();
  char advance();
  char peek();
  void addToken(TokenType type, std::string literal = "");
  void string();
  void number();
  char peekNext();
  bool identifier();

  bool isAtEnd();
  bool match(char expected);

public:
  Scanner(std::string source);
  std::vector<Token> scanTokens();
};