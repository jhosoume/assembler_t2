#ifndef INSTRUCTIONT
#define INSTRUCTIONT

#include <string>
#include <map>
#include <vector>

#include "Instruction.hpp"
#include "TokenType.hpp"
#include "Token.hpp"
#include "helper.hpp"

using ::std::string;
using ::std::map;
using ::std::pair;

class InstructionTable {
public:
  InstructionTable();
  void printInstructions();
  Instruction get(const string &);
  Instruction get(const Token &);
  bool isInstruction(const string &);
  bool isInstruction(const Token &);

  map<string, Instruction> instructions;

};

#endif
