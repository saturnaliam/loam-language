#include "include/scanner.hpp"
#include "include/token.hpp"
#include "include/interpret.hpp"
#include "include/Loam.hpp"
#include <iostream>
#include <fstream>
#include <typeinfo>
#define D(p) #p

// Initialization of static variables
bool Loam::hadError = false;
std::vector<Error> Loam::errors = {};

std::string loadFile(std::string filename);

int main(int argc, char** argv) {
  std::string contents = loadFile(argv[1]);

  Scanner scanner(contents);
  std::vector<Token> tokens = scanner.scanTokens();

  if (Loam::hadError) Loam::reportError();

  // for (Token token : tokens) {
  //   std::cout << token.toString() << "\n";
  // }

  // Parser parser(tokens);
  // std::unique_ptr<Expr> expression = parser.parse();

  Interpreter i(tokens);
  i.interpret();
}

/**
 * @brief Loads a file into a string.
 * @param filename The file to load.
 * @return The contents of the file.
 */
std::string loadFile(std::string filename) {
  std::ifstream file(filename);

  std::string contents, line;

  while (std::getline(file, line)) {
    contents += line + '\n';
  }

  return contents;
}