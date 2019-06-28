#ifndef SCANNER
#define SCANNER

#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <cctype>

#include "helper.hpp"
#include "TokenType.hpp"
#include "Token.hpp"
#include "InstructionTable.hpp"
#include "DirectiveTable.hpp"
#include "RegisterTable.hpp"

using ::std::string;
using ::std::vector;
using ::std::set;

class Scanner {
public:
  Scanner(InstructionTable, DirectiveTable, RegisterTable);
  // Split into Different tokens
  vector<Token> splitIntoTokens(string);
  // Classify each token
  TokenType classifyToken(string);
  bool isTokenValid(string);

private:
  bool checkValidNumberOfChars(const string &);
  bool checkIfSymbolStartsCorrectly(const string &);
  bool checkIfAllCharactersAreValid(const string &);
  bool checkIfHexNumber(const string &);
  bool checkIfDecNumber(const string &);

  InstructionTable instruction_table;
  DirectiveTable directive_table;
  RegisterTable register_table;

  set<char> validCharacters;
  set<char> validFirstCharacters;


};

#endif
