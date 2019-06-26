#ifndef SECONDP
#define SECONDP

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "Parser.hpp"
#include "Program.hpp"
#include "SymbolData.hpp"
#include "SymbolTable.hpp"
#include "Token.hpp"

using ::std::string;
using ::std::vector;
using ::std::cout;
using ::std::endl;

class SecondPass {
public:
  SecondPass(const Parser &,
             const Program &,
             const SymbolTable &,
             const InstructionTable &,
             const DirectiveTable &
           );
  void exec();
  void writeObjectFile();
  void showObjectCode();
  int getAddrValueFromOperand(vector <Token>, int);

private:
  Parser parser;
  Program program;
  SymbolTable symbol_table;
  InstructionTable instruction_table;
  DirectiveTable directive_table;
  vector<int> exec_code;

};


#endif
