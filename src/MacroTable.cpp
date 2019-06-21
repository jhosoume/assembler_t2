#include "MacroTable.hpp"

void MacroTable::printMacros() {
  cout << "------------------------------------" << endl;
  cout << "MACRO TABLE" << endl;
  for (const auto &pair_macro : macros) {
    Macro macro = pair_macro.second;
    cout << "Macro: " << macro.name << endl;
    cout << "   Operands: " << endl;
    for (auto operand : macro.operands_names) {
      cout << operand << " ";
    }
    cout << endl;
    cout << "   Def: " << endl;
    for (auto line : macro.macro_definition) {
      for (auto tok : line) {
        cout << tok.tvalue << " ";
      }
      cout << endl;
    }
    cout << "*******" <<  endl << endl;
  }
  cout << "------------------------------------" << endl;
}

bool MacroTable::isMacroDefined(const Token &symbol) {
  return isMacroDefined(symbol.tvalue);
}

bool MacroTable::isMacroDefined(const string &symbol) {
  return (macros.count(symbol) != 0);
}

Macro MacroTable::get(const string &macro_name) {
  return macros.at(macro_name);
}

void MacroTable::insert(string macro_name, Macro macro) {
  macros.insert(pair<string, Macro>(macro_name, macro));
}
