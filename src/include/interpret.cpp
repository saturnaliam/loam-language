#include "interpret.hpp"
#include "Loam.hpp"

void Interpreter::interpret() {
  currentToken = tokens[0];

  while (!isAtEnd()) {
    interpretToken();
  }
}

void Interpreter::interpretToken() {
  switch (currentToken.type) {
    case PLEASE:
      handlePlease();
      break;
    case GET:
      handleGet();
      break;
    case PUT:
      handlePut();
      break;
    case PUSH:
      handlePush();
      break;
    case DUMP:
      handleDump();
      break;
    case POP:
      handlePop();
      break;
    case EJECT:
      handleEject();
      break;
    case INJECT:
      handleInject();
      break;
    default:
      if (currentToken.type != _EOF) Loam::panic(currentToken.line, "Unexpected expression");
      break;
  }

  advance();
}

void Interpreter::handlePut() {
  if (!wasPolite) {
    Loam::panic(currentToken.line, "Programmer was impolite");
  }

  advance();

  if (currentToken.type == ONTO) {
    advance();

    if (currentToken.type == STDOUT) {
      std::cout << popReg;
      return;
    }
  }

  Loam::panic(currentToken.line, "Unexpected token.");
}

void Interpreter::handlePlease() {
  if (peek().type != GET && peek().type != PUT) {
    Loam::panic(currentToken.line, "Programmer polite at a strange time");
  }

  wasPolite = true;
}

void Interpreter::handlePush() {
  advance();

  if (currentToken.type == STRING) {
    deque.push(currentToken.literal);
  } else if (currentToken.type == FROM) {
    advance();

    if (currentToken.type == POPREG) {
      deque.push(popReg);
    } else if (currentToken.type == EJECTREG) {
      deque.push(ejectReg);
    } else {
      Loam::panic(currentToken.line, "Unexpected source");
    }
  } else {
    Loam::panic(currentToken.line, "Unexpected expression");
  }
}

void Interpreter::handleDump() {
  advance();

  if (currentToken.type == POPREG) {
    popReg = "";
  } else if (currentToken.type == EJECTREG) {
    ejectReg = "";
  } else {
    Loam::panic(currentToken.line, "Invalid register");
  }
}

void Interpreter::handlePop() {
  if (deque.size() == 0) Loam::panic(currentToken.line, "Cannot pop, deque empty");

  if (popReg != "") Loam::panic(currentToken.line, "Undumped register");

  popReg = deque.pop();
}

void Interpreter::handleGet() {
  advance();

  if (currentToken.type == FROM && peek().type == STDIN) {
    std::string input;
    std::cin >> input;
    deque.inject(input);
    advance();
  } else {
    Loam::panic(currentToken.line, "Unexpected expression.");
  }
}

void Interpreter::handleEject() {
  if (deque.size() == 0) Loam::panic(currentToken.line, "Cannot eject, deque empty");

  if (ejectReg != "") Loam::panic(currentToken.line, "Undumped register");

  ejectReg = deque.eject();
}

void Interpreter::handleInject() {
  advance();

  if (currentToken.type == STRING) {
    deque.inject(currentToken.literal);
  } else if (currentToken.type == FROM) {
    advance();

    if (currentToken.type == POPREG) {
      deque.inject(popReg);
    } else if (currentToken.type == EJECTREG) {
      deque.inject(ejectReg);
    } else {
      Loam::panic(currentToken.line, "Unexpected source");
    }
  } else {
    Loam::panic(currentToken.line, "Unexpected expression");
  }
}

bool Interpreter::isAtEnd() { return current >= tokens.size(); }

void Interpreter::advance() {
  if (current + 1 >= tokens.size()) {
    current++;
    currentToken = tokens.back();
  } else {
    current++;
    currentToken = tokens[current];
  }
}

Token Interpreter::peek() {
  if (current + 1 >= tokens.size()) return tokens.back();

  return tokens[current + 1];
}