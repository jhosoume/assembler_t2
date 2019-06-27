#ifndef REGISTERTB
#define REGISTERTB

#include <string>
#include <map>
#include <vector>

#include "Register.hpp"
#include "TokenType.hpp"
#include "Token.hpp"
#include "helper.hpp"

using ::std::string;
using ::std::map;
using ::std::pair;

class RegisterTable {
public:
  RegisterTable();
  void printRegisters();
  Register get(const string &);
  Register get(const Token &);
  bool isRegister(const string &);
  bool isRegister(const Token &);

  map<string, Register> registers;

};

#endif
