#include "EquTable.hpp"

bool EquTable::isEquDefined(const Token &symbol) {
  return isEquDefined(symbol.tvalue);
}

bool EquTable::isEquDefined(const string &symbol) {
  return (definitions.count(symbol) != 0);
}

Token EquTable::getEquToken(const Token &symbol) {
  return getEquToken(symbol.tvalue);
}

Token EquTable::getEquToken(const string &symbol) {
  return definitions.at(symbol);
}

void EquTable::addEqu(string symbol, Token ref) {
  if ( isEquDefined(symbol) ) {
    cout << "[SEMANTIC ERR] EQU symbol is being redefined!" << endl;
  }
  definitions.insert(pair <string, Token> (symbol, ref));
}

void EquTable::addEqu(Token token, Token ref) {
  addEqu(token.tvalue, ref);
}

void EquTable::listTable() {
  cout << "_________________________________________________________" << endl;
  cout << "Listing Equ Table" << endl;
  cout << "LABEL: Value" << endl;
  for (const auto &pair_symbol : definitions) {
    cout << pair_symbol.first << ": " << pair_symbol.second.tvalue << endl;
  }
  cout << "_________________________________________________________" << endl;
}
