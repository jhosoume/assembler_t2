#ifndef MT
#define MT

#include <iostream>
#include <string>

#include "Macro.hpp"

using ::std::string;
using ::std::map;
using ::std::pair;
using ::std::cout;
using ::std::endl;

class MacroTable {
public:
  void printMacros();

  bool isMacroDefined(const Token &);
  bool isMacroDefined(const string &);

  Macro get(const string &);
  void insert(string, Macro);

  map<string, Macro> macros;
};

#endif
