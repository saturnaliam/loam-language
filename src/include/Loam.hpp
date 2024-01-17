#pragma once
#include <iostream>
#include <string>
#include <vector>

/**
 * @brief Different types that errors can take.
 */
enum ErrorType {
  UNEXPECTED_SYMBOL,
  UNTERMINATED_STRING,
};

/**
 * @brief Any errors that was raised during execution.
 */
struct Error {
  int index;
  int line;
  ErrorType errorType;
  std::string problem; // The character that caused the issue (only for UNEXPECTED_SYMBOL)
};

/**
 * @brief A collection of functions needed for the language, that don't really fit anywhere else.
 */
class Loam {
private:
  /**
   * @brief Checks if the two errors are the same, and can be merged.
   * @param originalError The error at the back of the vector.
   * @param newError The error to be checked against.
   * @return If they are able to be merged.
   */
  static bool errorsMergeable(Error originalError, Error newError) {
    return (originalError.index == newError.index - 1 &&
      originalError.line == newError.line &&
      originalError.errorType == newError.errorType);
  }

public:
  static bool hadError;
  static std::vector<Error> errors;

  /**
   * @brief Marks that a line had an error, and what it was.
   * @param errorType The type of error.
   * @param index Where in the source it appeared.
   * @param line The current line.
   * @param problem The character causing the issue (only needed for UNEXPECTED_SYMBOL).
   */
  static void markError(ErrorType errorType, int index, int line, std::string problem = "") {
    Error newError = { .index = index, .line = line, .errorType = errorType, .problem = problem };

    if (errors.size() != 0) {
      if (errorsMergeable(errors.back(), newError)) {
        errors.back().problem += problem;
        errors.back().index = index;
      } else {
        errors.push_back(newError);
      }
    } else {
      errors.push_back(newError);
    }

    hadError = true;
  }

  [[noreturn]] static void panic(int line, std::string message) {
    std::string reportedError = "[line " + std::to_string(line) + "] Error: " + message + ".";
    std::cerr << reportedError;
    exit(65);
  }

  /**
   * @brief Prints out all collected errors from the program.
   */
  static void reportError() {
    for (Error error : errors) {
      std::string buffer = "[line " + std::to_string(error.line) + "] Error: ";

      switch (error.errorType) {
        case UNEXPECTED_SYMBOL:
          buffer += "Unexpected symbol '" + error.problem + "'";
          break;
        case UNTERMINATED_STRING:
          buffer += "Unterminated string";
          break;
      }

      std::cerr << buffer << ".\n";
    }

    exit(65);
  }
};