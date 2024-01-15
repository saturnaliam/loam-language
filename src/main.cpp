#include "include/scanner.hpp"
#include "include/token.hpp"
#include "include/Loam.hpp"
#include <iostream>
#include <fstream>

// Initialization of static variables
bool Loam::hadError = false;
std::vector<Error> Loam::errors = {};

int main(void) {
  // TODO: clean up file reading code
  std::ifstream file("../test.lm");

  std::string contents, line;

  while (std::getline(file, line)) {
    contents += line + '\n';
  }

  Scanner scanner(contents);
  std::vector<Token> tokens = scanner.scanTokens();

  if (Loam::hadError) Loam::reportError();
  for (auto token : tokens) {
    std::cout << token.toString() << "\n";
  }
}