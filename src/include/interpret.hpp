#pragma once
#include "token.hpp"
#include "Loam.hpp"
#include <vector>
#include <iostream>
#include <string>

template <typename T>
class Deque {
private:
  std::vector<T> list = {};
public:
  T eject() {
    T back = list.back();
    list.pop_back();
    return back;
  }

  T pop() {
    T front = list.front();
    list.erase(list.begin(),list.begin()+1);
    return front;
  }

  void inject(T value) {
    list.push_back(value);
  }

  void push(T value) {
    list.insert(list.begin(), value);
  }

  size_t size() {
    return list.size();
  }
};

class Interpreter {
private:
  bool isAtEnd();
  void advance();
  Token peek();
  void interpretToken();

  void handlePlease();
  void handlePut();
  void handleGet();
  void handlePush();
  void handleDump();
  void handlePop();
  void handleEject();
  void handleInject();

  Token currentToken;
  int current = 0;
  std::string popReg;
  std::string ejectReg;
  bool wasPolite = false;
  std::vector<Token> tokens;
  Deque<std::string> deque;


public:
  Interpreter(std::vector<Token> tokens) {
    this->tokens = tokens;
  }

  void interpret();
};