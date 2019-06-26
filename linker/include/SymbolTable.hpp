#ifndef SYMBOLTABLE
#define SYMBOLTABLE

#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <cctype>

#include "SymbolData.hpp"
#include "Token.hpp"
#include "helper.hpp"

using ::std::string;
using ::std::map;
using ::std::pair;
using ::std::cout;
using ::std::endl;
using ::std::pair;

class SymbolTable {
public:
  bool isSymbolDefined(const Token &);
  bool isSymbolDefined(const string &);

  int getSymbolAddress(const Token &);
  int getSymbolAddress(const string &);

  int getSymbolOffset(const Token &);
  int getSymbolOffset(const string &);

  SymbolData getSymbolData(const Token &);
  SymbolData getSymbolData(const string &);


  void addSymbol(int, string, int, SymbolType, int, int);
  void addSymbol(int, string, int);
  void addSymbol(int, Token, int);

  void listTable();

private:
  map<string, SymbolData> definitions;
};

#endif
