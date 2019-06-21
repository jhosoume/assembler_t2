#ifndef DIRECTIVECLASS
#define DIRECTIVECLASS

#include <string>
#include <vector>
#include <iostream>

#include "TokenType.hpp"

using ::std::string;
using ::std::vector;
using ::std::cout;
using ::std::endl;

class Directive {
public:
  Directive(string, int, int);

  string name;
  int max_operands; //Max number of operands
  int size; //Max number of operands
  // [INSTRUCTION SYMBOL, INSTRUCTION SYMBOL ADD_SYMBOL NUMBER_DECIMAL]
  vector<vector<TokenType>> signatures;

};

#endif
