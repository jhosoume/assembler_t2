#ifndef FIRSTP
#define FIRSTP

#include <iostream>
#include <string>

#include "Parser.hpp"
#include "InstructionTable.hpp"
#include "DirectiveTable.hpp"
#include "Program.hpp"
#include "SymbolTable.hpp"

using ::std::string;
using ::std::cout;
using ::std::endl;

class FirstPass {
public:
  FirstPass(const Parser &, const Program &, const InstructionTable &, const DirectiveTable &);
  SymbolTable exec();

private:
  Parser parser;
  Program program;
  InstructionTable instruction_table;
  DirectiveTable directive_table;
};


#endif
