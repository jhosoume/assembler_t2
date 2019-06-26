#include "DirectiveTable.hpp"

DirectiveTable::DirectiveTable() {
  vector<TokenType> signature;
  // CONST _________________________________________________________
  directives.insert( pair<string, Directive>( "CONST", Directive("CONST", 1, 1) ) );
  signature.push_back(TokenType::DIRECTIVE_TOKEN);
  signature.push_back(TokenType::NUMBER_DECIMAL);
  directives.at("CONST").signatures.push_back(signature);
  signature.clear();
  signature.push_back(TokenType::DIRECTIVE_TOKEN);
  signature.push_back(TokenType::NUMBER_HEX);
  directives.at("CONST").signatures.push_back(signature);
  signature.clear();
  signature.push_back(TokenType::DIRECTIVE_TOKEN);
  signature.push_back(TokenType::SYMBOL); //In case of EQU
  directives.at("CONST").signatures.push_back(signature);
  signature.clear();

  // SECTION _________________________________________________________
  directives.insert( pair<string, Directive>( "SECTION", Directive("SECTION", 1, 0) ) );
  signature.push_back(TokenType::DIRECTIVE_TOKEN);
  signature.push_back(TokenType::DATA_SECTION);
  directives.at("SECTION").signatures.push_back(signature);
  signature.clear();
  signature.push_back(TokenType::DIRECTIVE_TOKEN);
  signature.push_back(TokenType::TEXT_SECTION);
  directives.at("SECTION").signatures.push_back(signature);
  signature.clear();

  // SPACE _________________________________________________________
  // TODO! Check, space has variable size, depending on number
  directives.insert( pair<string, Directive>( "SPACE", Directive("SPACE", 1, -1) ) );
  signature.push_back(TokenType::DIRECTIVE_TOKEN);
  directives.at("SPACE").signatures.push_back(signature);
  signature.clear();
  signature.push_back(TokenType::DIRECTIVE_TOKEN);
  signature.push_back(TokenType::NUMBER_DECIMAL);
  directives.at("SPACE").signatures.push_back(signature);
  signature.clear();
  // signature.push_back(TokenType::DIRECTIVE_TOKEN);
  // signature.push_back(TokenType::NUMBER_HEX);
  // directives.at("SPACE").signatures.push_back(signature);
  // signature.clear();
  // signature.push_back(TokenType::DIRECTIVE_TOKEN);
  // signature.push_back(TokenType::SYMBOL);
  // directives.at("SPACE").signatures.push_back(signature);
  // signature.clear();

  // EQU _________________________________________________________
  directives.insert( pair<string, Directive>( "EQU", Directive("EQU", 1, 0) ) );
  preprocess_dirs.insert( pair<string, Directive>( "EQU", Directive("EQU", 1, 0) ) );
  signature.push_back(TokenType::DIRECTIVE_TOKEN);
  signature.push_back(TokenType::NUMBER_DECIMAL);
  directives.at("EQU").signatures.push_back(signature);
  signature.clear();
  signature.push_back(TokenType::DIRECTIVE_TOKEN);
  signature.push_back(TokenType::NUMBER_HEX);
  directives.at("EQU").signatures.push_back(signature);
  signature.clear();
  // signature.push_back(TokenType::DIRECTIVE_TOKEN);
  // signature.push_back(TokenType::SYMBOL); //In case it refers to another EQU for some reason
  // directives.at("EQU").signatures.push_back(signature);
  // signature.clear();

  // IF _________________________________________________________
  directives.insert( pair<string, Directive>( "IF", Directive("IF", 1, 0) ) );
  preprocess_dirs.insert( pair<string, Directive>( "IF", Directive("IF", 1, 0) ) );
  signature.push_back(TokenType::DIRECTIVE_TOKEN);
  signature.push_back(TokenType::SYMBOL);
  directives.at("IF").signatures.push_back(signature);
  signature.clear();
  signature.push_back(TokenType::DIRECTIVE_TOKEN);
  signature.push_back(TokenType::NUMBER_DECIMAL);
  directives.at("IF").signatures.push_back(signature);
  signature.clear();

  // MACRO _________________________________________________________
  directives.insert( pair<string, Directive>( "MACRO", Directive("MACRO", 0, 0) ) );
  preprocess_dirs.insert( pair<string, Directive>( "MACRO", Directive("MACRO", 0, 0) ) );
  signature.push_back(TokenType::DIRECTIVE_TOKEN);
  directives.at("MACRO").signatures.push_back(signature);
  signature.clear();

  // ENDMACRO  _________________________________________________________
  directives.insert( pair<string, Directive>( "END", Directive("END", 0, 0) ) );
  preprocess_dirs.insert( pair<string, Directive>( "END", Directive("END", 0, 0) ) );
  signature.push_back(TokenType::DIRECTIVE_TOKEN);
  directives.at("END").signatures.push_back(signature);
  signature.clear();

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
