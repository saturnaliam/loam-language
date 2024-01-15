#include "token.hpp"

/**
 * @brief Returns the name of a type.
 *
 */
#define PROCESS_VAL(p)                                                         \
  case (p):                                                                    \
    return #p;

/**
 * @brief Converts a TokenType into a string.
 *
 * @param type The type to convert.
 * @return The stringified of the TokenType.
 */
std::string typeToString(TokenType type) {
  switch (type) {
    PROCESS_VAL(L_PAREN);
    PROCESS_VAL(R_PAREN);
    PROCESS_VAL(L_BRACE);
    PROCESS_VAL(R_BRACE);
    PROCESS_VAL(MINUS);
    PROCESS_VAL(PLUS);
    PROCESS_VAL(SLASH);
    PROCESS_VAL(ASTERISK);
    PROCESS_VAL(BANG);
    PROCESS_VAL(BANG_EQUAL);
    PROCESS_VAL(EQUAL_EQUAL);
    PROCESS_VAL(GREATER);
    PROCESS_VAL(GREATER_EQUAL);
    PROCESS_VAL(LESS);
    PROCESS_VAL(LESS_EQUAL);
    PROCESS_VAL(STRING);
    PROCESS_VAL(NUMBER);
    PROCESS_VAL(PUSH);
    PROCESS_VAL(POP);
    PROCESS_VAL(EJECT);
    PROCESS_VAL(INJECT);
    PROCESS_VAL(DUMP);
    PROCESS_VAL(EJECTREG);
    PROCESS_VAL(POPREG);
    PROCESS_VAL(PLEASE);
    PROCESS_VAL(PUT);
    PROCESS_VAL(ONTO);
    PROCESS_VAL(FROM);
    PROCESS_VAL(GET);
    PROCESS_VAL(STDOUT);
    PROCESS_VAL(STDIN);
    PROCESS_VAL(IF);
    PROCESS_VAL(OR);
    PROCESS_VAL(AND);
    PROCESS_VAL(_EOF);
  }
}

std::string operator+(TokenType lhs, std::string rhs) {
  return typeToString(lhs) + rhs;
}

/**
 * @brief Construct a new Token
 *
 * @param type The ``TokenType`` to add.
 * @param lexeme The lexeme to add.
 * @param line The line number of the token.
 * @param literal The literal value (optional).
 */
Token::Token(TokenType type, std::string lexeme, int line,
             std::string literal) {
  this->type = type;
  this->lexeme = lexeme;
  this->line = line;
  this->literal = literal;
}

/**
 * @brief Stringifies a token.
 * @return The formatted token.
 */
std::string Token::toString() {
  return type + std::string(" ") + ( literal == "" ? lexeme : literal);
}