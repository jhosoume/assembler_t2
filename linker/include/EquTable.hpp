#ifndef EQUTABLE
#define EQUTABLE

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

class EquTable {
public:
  bool isEquDefined(const Token &);
  bool isEquDefined(const string &);

  Token getEquToken(const Token &);
  Token getEquToken(const string &);

  void addEqu(string, Token);
  void addEqu(Token, Token);

  void listTable();

private:
  map<string, Token> definitions;
};

#endif
