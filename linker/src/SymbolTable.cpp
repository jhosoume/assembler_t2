#include "SymbolTable.hpp"

bool SymbolTable::isSymbolDefined(const Token &symbol) {
  return isSymbolDefined(symbol.tvalue);
}

bool SymbolTable::isSymbolDefined(const string &symbol) {
  return (definitions.count(symbol) != 0);
}

int SymbolTable::getSymbolAddress(const Token &symbol) {
  return getSymbolAddress(symbol.tvalue);
}

int SymbolTable::getSymbolAddress(const string &symbol) {
  return definitions.at(symbol).address;
}

int SymbolTable::getSymbolOffset(const Token &symbol) {
  return getSymbolOffset(symbol.tvalue);
}

int SymbolTable::getSymbolOffset(const string &symbol) {
  return definitions.at(symbol).offset;
}

SymbolData SymbolTable::getSymbolData(const Token &symbol) {
  return getSymbolAddress(symbol.tvalue);
}

SymbolData SymbolTable::getSymbolData(const string &symbol) {
  return definitions.at(symbol);
}

void SymbolTable::addSymbol(int line, string symbol, int addr, SymbolType s_type, int value, int vec_size) {
  SymbolData s_data = SymbolData(addr, value, s_type, vec_size);
  if ( isSymbolDefined(symbol) ) {
    cout << "[SEMANTIC ERR] Line: " << line + 1 << " | Symbol is being redefined!" << endl;
  }
  definitions.insert(pair <string, SymbolData> (symbol, s_data));
}

void SymbolTable::addSymbol(int line, Token token, int addr) {
  addSymbol(line, token.tvalue, addr);
}

void SymbolTable::addSymbol(int line, string symbol, int addr) {
  addSymbol(line, symbol, addr, SymbolType::INSTRUCTION, 0, 0);
}

void SymbolTable::listTable() {
  cout << "Listing Symbol Table" << endl;
  cout << "LABEL: Address" << endl;
  for (const auto &pair_symbol : definitions) {
    cout << pair_symbol.first << ": ";
    cout << std::hex << pair_symbol.second.address << " "
      << SymbolTypeToString(pair_symbol.second.symbol_type) << " " << pair_symbol.second.value
      << " "<< pair_symbol.second.offset << endl;
  }
}
