#include "scanner.hpp"
#include <string>

Scanner::Scanner(std::string source) { this->source = source; }

std::vector<Token> Scanner::scanTokens() {
  while (!isAtEnd()) {
    start = current;
    scanToken();
  }

  tokens.push_back(Token(_EOF, "", line));
  return tokens;
}

/**
 * @brief Detects if the scanner has gone through the entire source.
 * @return Whether the scanner is at the end of the source.
 */
bool Scanner::isAtEnd() { return current >= source.length(); }

/**
 * @brief Scans the next token.
 */
void Scanner::scanToken() {
  char c = advance();

  switch (c) {
    case '(': addToken(L_PAREN); break;
    case ')': addToken(R_PAREN); break;
    case '{': addToken(L_BRACE); break;
    case '}': addToken(R_BRACE); break;
    case '-': addToken(MINUS); break;
    case '+': addToken(PLUS); break;
    case '*': addToken(ASTERISK); break;
    case '!':
      addToken(match('=') ? BANG_EQUAL : BANG);
      break;
    case '<':
      addToken(match('=') ? LESS_EQUAL : LESS);
      break;
    case '>':
      addToken(match('=') ? GREATER_EQUAL : GREATER);
      break;

    case '/':
      if (match('/')) {
        while (peek() != '\n' && !isAtEnd()) advance();
      } else {
        addToken(SLASH);
      }
      break;

    case ' ': // handling whitespace
    case '\r':
    case '\t':
      break;

    case '\n':
      line++;
      break;

    case '"':
      string();
      break;

    default:
      if (isdigit(c)) {
        number();
      } else {
        if (identifier()) break;
        Loam::markError(UNEXPECTED_SYMBOL, current, line, std::string(1, c));
      }
      break;
  }
}

/**
 * @brief Consumes the next character.
 * @return The consumed character.
 */
char Scanner::advance() {
  return source.at(current++);
}

/**
 * @brief Adds a token to the back of the ``tokens`` vector.
 * @param type The ``TokenType`` to add.
 * @param literal The literal value (optional)
 */
void Scanner::addToken(TokenType type, std::string literal) {
  std::string lexeme = source.substr(start, current - start);

  tokens.push_back(Token(type, lexeme, line, literal));
}

/**
 * @brief Determines if the next unconsumed character is equal to an expected one, consumes it if so.
 * @param expected The expected character.
 * @return If the next unconsumed character is equal to expected.
 */
bool Scanner::match(char expected) {
  if (isAtEnd()) return false;
  if (source.at(current) != expected) return false;

  current++;
  return true;
}

/**
 * @brief Checks the next character without consuming it.
 * @return The character.
 */
char Scanner::peek() {
  if (isAtEnd()) return '\0';

  return source.at(current);
}

/**
 * @brief Processes a string.
 */
void Scanner::string() {
  while (peek() != '"' && !isAtEnd()) {
    if (peek() == '\n') line++;
    advance();
  }

  if (isAtEnd()) {
    Loam::markError(UNTERMINATED_STRING, current, line);
    return;
  }

  advance();

  std::string value = source.substr(start + 1, current - start - 2);
  addToken(STRING, value);
}

/**
 * @brief Scans in a number.
 */
void Scanner::number() {
  while (isdigit(peek())) advance();

  if (peek() == '.' && isdigit(peekNext())) {
    advance();

    while (isdigit(peek())) advance();
  }

  std::string value = source.substr(start, current - start);
  addToken(NUMBER, value);
}

/**
 * @brief Checks the character 2 in advance.
 * @return The character.
 */
char Scanner::peekNext() {
  if (current + 1 >= source.size()) return '\0';
  return source.at(current + 1);
}

/**
 * @brief Checks if the upcoming symbol is a keyword, and tokenizes it if so.
 * @return True if a keyword, false if not.
 */
bool Scanner::identifier() {
  while (isalpha(peek())) advance();

  std::string value = source.substr(start, current - start);

  if (keywords.find(value) == keywords.end()) {
    return false;
  } else {
    TokenType type = keywords.find(value)->second;
    addToken(type);
    return true;
  }
}