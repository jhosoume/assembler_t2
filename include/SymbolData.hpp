#ifndef SYMBOLDATA
#define SYMBOLDATA

#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <cctype>

#include "Token.hpp"

using ::std::string;
using ::std::map;
using ::std::pair;
using ::std::cout;
using ::std::endl;
using ::std::pair;

enum class SymbolType {
  CONST,
  SPACE,
  INSTRUCTION
};


class SymbolData {
public:

  SymbolData(int);
  SymbolData(int, SymbolType);
  SymbolData(int, int, SymbolType);
  SymbolData(int, int, SymbolType, int);

  int address;
  int value;
  SymbolType symbol_type;
  int offset;

};

#endif
