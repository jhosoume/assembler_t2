#ifndef TRLATE
#define TRLATE

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "Parser.hpp"
#include "Program.hpp"
#include "Token.hpp"

using ::std::string;
using ::std::vector;
using ::std::cout;
using ::std::endl;

class Translate {
public:
  Translate(const Parser &,
            const Program &
           );
  void exec();
  void writeNasmFile();
  void showNasmCode();

private:
  Parser parser;
  Program program;
  vector<string> nasm_code;

};


#endif
