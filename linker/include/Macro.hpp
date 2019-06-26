#ifndef MAC
#define MAC

#include <string>
#include <vector>
#include <map>

#include "Token.hpp"

using ::std::string;
using ::std::vector;
using ::std::map;
using ::std::pair;

class Position {
public:
  int line;
  int indx;
};


class Macro {
public:
  Macro();
  Macro(string);

  int getNumOperands();
  void addOperand(string);
  int operandIndx(string);
  int operandIndx(Token);
  void addOperandPosition(string, int, int);
  void addMacroLines(vector<Token>);
  string name;

  vector <string> operands_names;
  map <string, vector< Position > > operands_positions;
  vector < vector<Token> > macro_definition;
};

#endif
