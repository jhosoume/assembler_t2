#include "DirectiveTable.hpp"

DirectiveTable::DirectiveTable() {
  vector<TokenType> signature;
  // DD _________________________________________________________
  directives.insert( pair<string, Directive>( "DD", Directive("DD", 1000, 4) ) );
}

// Print all possible signtures of all directives
void DirectiveTable::printDirectives() {
  for (const auto &pair_directive : directives) {
    Directive directive = pair_directive.second;
    cout << " Directive: " << directive.name << endl;
    cout << "   Signatures: " << endl;
    cout << "         Size: " << directive.size << endl;
    for (auto signature : directive.signatures) {
      cout << "       ";
      for (TokenType toktype : signature) {
        cout << TokenTypeToString(toktype) << " ";
      }
      cout << endl;
    }
  }
}

Directive DirectiveTable::get(const string &token_value) {
  return directives.at(token_value);
}

Directive DirectiveTable::get(const Token &token) {
  return directives.at(token.tvalue);
}

bool DirectiveTable::isPreProcessDirective(const string &token_value) {
  return (preprocess_dirs.count(token_value) >= 0);
}

bool DirectiveTable::isPreProcessDirective(const Token &token) {
  return (preprocess_dirs.count(token.tvalue) >= 0);
}

bool DirectiveTable::isDirective(const Token &token) {
  return isDirective(token.tvalue);
}

bool DirectiveTable::isDirective(const string &token_value) {
  return (directives.count(token_value) != 0);
}
