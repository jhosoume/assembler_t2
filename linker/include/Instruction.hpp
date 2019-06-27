#ifndef INSTRUCTIONCLASS
#define INSTRUCTIONCLASS

#include <string>
#include <vector>
#include <iostream>

#include "TokenType.hpp"

using ::std::string;
using ::std::vector;
using ::std::cout;
using ::std::endl;

class Instruction {
public:
/*  Instruction(string, int, int, int);

  string name;
  int num_operands;
  int op_code;
  int size;
  // [INSTRUCTION SYMBOL, INSTRUCTION SYMBOL ADD_SYMBOL NUMBER_DECIMAL]
  vector<vector<TokenType>> signatures;*/
  Instruction(string, int, int, int);

    string name;
    int num_operands;
    int op_code;
    int size;
    // [INSTRUCTION SYMBOL, INSTRUCTION SYMBOL ADD_SYMBOL NUMBER_DECIMAL]
    vector<vector<TokenType>> signatures;

};

#endif
