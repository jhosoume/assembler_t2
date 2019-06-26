#ifndef DIRECTIVET
#define DIRECTIVET

#include <string>
#include <map>
#include <vector>

#include "Directive.hpp"
#include "TokenType.hpp"
#include "Token.hpp"
#include "helper.hpp"

using ::std::string;
using ::std::map;
using ::std::pair;

class DirectiveTable {
public:
  DirectiveTable();
  void printDirectives();
  Directive get(const string &);
  Directive get(const Token &);
  bool isPreProcessDirective(const string &);
  bool isPreProcessDirective(const Token &);
  bool isDirective(const string &);
  bool isDirective(const Token &);

  map<string, Directive> directives;
  map<string, Directive> preprocess_dirs;

};

#endif
