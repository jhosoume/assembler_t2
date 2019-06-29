#ifndef PROGRAM
#define PROGRAM

#include <string>
#include <map>
#include <vector>

#include "Token.hpp"
#include "SymbolTable.hpp"
#include "helper.hpp"

using ::std::string;
using ::std::map;
using ::std::vector;

class Program {
public:
  Program(File);

  void showTokenswithType();
  void showTokens();

  int num_lines;
  File file;
  int total_size;
  int text_size;
  int data_size;
  int data_section;
  int text_section;
  std::vector< std::vector<Token> > tokens;

};

#endif
