#ifndef SECONDP
#define SECONDP

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <elfio/elfio.hpp>

#include "Parser.hpp"
#include "Program.hpp"
#include "SymbolData.hpp"
#include "SymbolTable.hpp"
#include "RegisterTable.hpp"
#include "InstructionTable.hpp"
#include "SymbolTable.hpp"
#include "Token.hpp"

using ::std::string;
using ::std::vector;
using ::std::cout;
using ::std::endl;

using namespace ELFIO;

class SecondPass {
public:
  SecondPass(const Parser &,
             const Program &,
             const SymbolTable &,
             const InstructionTable &,
             const DirectiveTable &,
             const RegisterTable &
           );
  void exec();
  void writeObjectFile();
  void showObjectCode();
  void showTextCode();
  void showDataCode();
  int getAddrValueFromOperand(vector <Token>, int);

private:
  Parser parser;
  Program program;
  SymbolTable symbol_table;
  InstructionTable instruction_table;
  DirectiveTable directive_table;
  RegisterTable register_table;
  vector<int> exec_code;
  vector<char> text_code;
  vector<char> data_code;
  int begin_data = 0x08148000;
  int offset_ReadChar = 0;
  int offset_WriteChar = 45;
  int offset_ReadInt = 94;
  int offset_WriteInt = 230;
  int offset_ReadHex = 395;
  int offset_WriteHex = 509;
  int offset_ReadString = 645;
  int offset_WriteString = 669;
  void getBytes(int, char []);
  int bigToLittle(int);
  string stringfyOps(vector <Token>);
  int calculateJump(vector <Token>, int, int);
  int calculateCall(vector <Token>, int, int, int);
  void createExec();
  void appendIOCode();
};


#endif
