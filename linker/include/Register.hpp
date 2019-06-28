#ifndef REGISTERC
#define REGISTERC

#include <string>
#include <vector>
#include <iostream>

#include "TokenType.hpp"

using ::std::string;
using ::std::vector;
using ::std::cout;
using ::std::endl;

class Register {
public:
/*  Register(string, int, int, int);

  string name;
  int num_operands;
  int op_code;
  int size;
  // [INSTRUCTION SYMBOL, INSTRUCTION SYMBOL ADD_SYMBOL NUMBER_DECIMAL]
  vector<vector<TokenType>> signatures;*/
  Register(string, int);

    string name;
    int op_code;

};

#endif
